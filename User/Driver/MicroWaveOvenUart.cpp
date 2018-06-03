#include "Driver/MicroWaveOvenUart.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * @微波炉串口
 * @brief 接收缓冲区
 */
static uint64_t RecvBuffer[512 / 8];
static uint64_t RecvSingleBuffer[64 / 8];

static MicroWaveOvenUartEvent MsgRecv;


MicroWaveOvenUart::MicroWaveOvenUart(void) : 
	Receiver("MicroWaveOven", aMqMem, MICRO_WAVE_OVEN_MESSAGE_OBJ_NUMBER, MICRO_WAVE_OVEN_MESSAGE_OBJ_SIZE),
	Sender("MicroWaveOven")
{
	initDriver();
}

void MicroWaveOvenUart::write(const char *format, ...)
{
	static char buffer[100];
	va_list ap;
	
	va_start(ap, format);
	int len = vsprintf(buffer, format, ap);
	write((const uint8_t *) buffer, len);
}

/**
 * @brief PB10 <-> USART3_TX, PB11 <-> USART3_RX, AF7
 * 		  					  DMA1_Stream1_Channel4
 */
void MicroWaveOvenUart::initDriver(void)
{
	RCC->AHB1ENR |= 0x02; // Enable GpioB
	RCC->APB1ENR |= 0x40000; // Enable USART3
	RCC->AHB1ENR |= 0x200000; // Enable DMA1
	
	GPIOB->MODER &= ~0xF00000;
	GPIOB->MODER |= 0xA00000;
	
	GPIOB->PUPDR &= ~0xF00000;
	GPIOB->PUPDR |= 0x500000;
	
	GPIOB->OSPEEDR |= 0xA00000;
	
	GPIOB->OTYPER &= ~0xC00;
	
	GPIOB->AFR[1] &= ~0xFF00;
	GPIOB->AFR[1] |= 0x7700;
	
	USART3->CR1 = 0x00;
	USART3->CR2 = 0x00;
	USART3->CR3 = 0x40;
	USART3->BRR = 42000000 / 115200;
	USART3->CR1 = 0x201C;
	
	DMA1->LIFCR = 0xFC0;
	DMA1_Stream1->CR = 0x00;
	DMA1_Stream1->M0AR = (uint32_t) &RecvBuffer;
	DMA1_Stream1->PAR = (uint32_t) &USART3->DR;
	DMA1_Stream1->NDTR = sizeof (RecvBuffer);
	DMA1_Stream1->CR = 	(0x04 << 25) | // 第四通道
						(0x00 << 23) | // 存储器单次传输
						(0x00 << 21) | // 外设单次传输
						(0x00 << 19) | // 使用M0
						(0x00 << 18) | // 不使用双缓冲区
						(0x02 << 16) | // 优先级高
						(0x00 << 15) | // 外设偏移量与PSIZE相关
						(0x00 << 13) | // 存储器大小为8位
						(0x00 << 11) | // 外设大小为8位
						(0x01 << 10) | // 每次数据传输以后存储器地址递增
						(0x00 << 9) | // 外设地址不递增
						(0x01 << 8) | // 循环模式
						(0x00 << 6) | // 数据传输方向: 外设到存储器
						(0x00 << 5) | // 外设是流控制器
						(0x01 << 0) ; // 使能DMA
	NVIC_EnableIRQ(USART3_IRQn);	
}

static inline void vBufferOver(uint32_t index, uint32_t lastIndex)
{
	uint32_t k = 0;
	uint8_t *p1 = (uint8_t *) RecvSingleBuffer;
	uint8_t *p2 = (uint8_t *) RecvBuffer;
	for (uint32_t i = lastIndex; i < sizeof (RecvBuffer); i ++, k ++) {
		p1[k] = p2[i];
	}
	for (uint32_t i = 0; i < index; i ++, k ++) {
		p1[k] = p2[i];
	}
	MsgRecv.set(p1, k);
}

extern "C" void USART3_IRQHandler(void)
{
	static uint32_t lastIndex;
	uint32_t index;
	if (0 == (USART3->SR & 0x10)) {
		return ;
	}
	index = USART3->DR;
	index = sizeof(RecvBuffer) - DMA1_Stream1->NDTR;
	if (index > lastIndex) {
		MsgRecv.set((const uint8_t *) (RecvBuffer) + lastIndex, index - lastIndex);
	} else {
		vBufferOver(index, lastIndex);
	}
	MicroWaveOvenUart::instance()->put(&MsgRecv);
	lastIndex = index;
}





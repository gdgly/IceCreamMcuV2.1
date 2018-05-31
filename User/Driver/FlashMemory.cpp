#include "Driver/FlashMemory.h"

#define READ_STATUS			0x05 // 读状态寄存器指令
#define WRITE_ENABLE		0x06 // 写使能
#define READ_ID				0x90 // 读ID
#define SECTOR_EARSE		0x20 // 扇区擦除
#define READ_DATA			0x03 // 读数据
#define PAGE_PROGRAM		0x02 // 页编程


FlashMempry::FlashMempry(void)
{
	initSpiInterface();
}

void FlashMempry::vWriteData(uint32_t address, const uint8_t *data, uint32_t size)
{
	if (address & 0xFF) // 地址没有256字节对齐
	{
		uint32_t residue = (address + 0xFF) & (~0xFF);
		
	}
}

void FlashMempry::vReadData(uint32_t address, uint8_t *data, uint32_t size)
{
	vCsLow();
	xTranslateByte(address >> 16);
	xTranslateByte(address >> 8);
	xTranslateByte(address & 0xFF);
	while (size --)
	{
		*data = xTranslateByte(0xFF);
		data ++;
	}
	vCsHigh();
}

void FlashMempry::vPageProgram(uint32_t address, const uint8_t *data, uint32_t size)
{
	vWriteEnable();
	
	vCsLow();
	xTranslateByte(PAGE_PROGRAM);
	xTranslateByte(address >> 16);
	xTranslateByte(address >> 8);
	xTranslateByte(address & 0xFF);
	while (size --) {
		xTranslateByte(*data ++);
	}
	vCsHigh();
}

void FlashMempry::vSectorEarse(uint32_t address)
{
	vWriteEnable();
	
	vCsLow();
	xTranslateByte(SECTOR_EARSE);
	xTranslateByte(address >> 16);
	xTranslateByte(address >> 8);
	xTranslateByte(address & 0xFF);
	vCsHigh();
	
	while (xQueryStatus() & 0x01) {
		osDelay(5);
	}
}

void FlashMempry::vWriteEnable(void)
{
	vCsLow();
	xTranslateByte(WRITE_ENABLE);
	vCsHigh();
}

uint8_t FlashMempry::xQueryStatus(void)
{
	uint8_t ret;
	vCsLow();
	xTranslateByte(READ_STATUS);
	ret = xTranslateByte(0xFF);
	vCsHigh();
	return ret;
}

uint8_t FlashMempry::xTranslateByte(uint8_t byte)
{
	while (0 == (SPI3->SR & 0x02));
	SPI3->DR = byte;
	while (0 == (SPI3->SR & 0x01));
	return SPI3->DR;
}

/**
 * @brief 
 * PB6 <-> CS
 * PB3 <-> SPI3_SCK
 * PB4 <-> SPI3_MISO
 * PB5 <-> SPI3_MOSI
 */
void FlashMempry::initSpiInterface(void)
{
	RCC->AHB1ENR |= 0x02;
	
	GPIOB->MODER &= ~0x3FC0;
	GPIOB->MODER |= 0x1A80;
	GPIOB->PUPDR &= ~0x3FC0;
	GPIOB->PUPDR |= 0x1540;
	GPIOB->OSPEEDR |= 0x3FC0;
	GPIOB->OTYPER &= ~0x78;
	GPIOB->AFR[0] &= ~0xFFF000;
	GPIOB->AFR[0] |= 0x666000;
	
	RCC->APB1ENR |= 0x8000;
	
	SPI3->CR1 = 0x00;
	SPI3->I2SCFGR = 0x00;
	SPI3->CR2 = 0x00;
	SPI3->CR1 = 0x0344;
	
	vCsHigh();
}












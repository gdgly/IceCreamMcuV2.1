#ifndef		__MICRO_WAVE_OVEN_UART_H
#define		__MICRO_WAVE_OVEN_UART_H

#include "stm32f4xx.h"
#include "MessageReceiver.h"

#define MICRO_WAVE_OVEN_MESSAGE_OBJ_SIZE		sizeof (MessageReceiver)
#define MICRO_WAVE_OVEN_MESSAGE_OBJ_NUMBER		10
#define MICRO_WAVE_OVEN_MESSAGE_SIZE			osRtxMessageQueueMemSize(MICRO_WAVE_OVEN_MESSAGE_OBJ_NUMBER, MICRO_WAVE_OVEN_MESSAGE_OBJ_SIZE)

class MicroWaveOvenUart
{
	public:
		inline static MicroWaveOvenUart *instance(void)
		{			
			static MicroWaveOvenUart uart;
			return &uart;
		}
	
	public:
		MicroWaveOvenUart(void);
	
		inline void putMessage(const MessageReceiver *msg)
		{
			osMessageQueuePut(sMqId, msg, 0, 0);
		}
		
		inline void getMessage(MessageReceiver *msg) 
		{
			osMessageQueueGet(sMqId, msg, NULL, osWaitForever);
		}
		
		inline void write(uint8_t byte) 
		{
			while (0 == (USART3->SR & 0x80));
			USART3->DR = byte;
		}
		
		inline void write(const uint8_t *byteArray, uint32_t len) 
		{
			osMutexAcquire(sMutexId, osWaitForever);
			while (len --) 
			{
				write(*byteArray);
				byteArray ++;
			}
			osMutexRelease(sMutexId);
		}
		
		inline MicroWaveOvenUart& operator<<(const char *str)
		{
			osMutexAcquire(sMutexId, osWaitForever);
			while (*str != '\0')
			{
				write((uint8_t) *str);
				str ++;
			}
			osMutexRelease(sMutexId);
			return *this;
		}
		
		MicroWaveOvenUart& operator<<(int32_t number);
	
	private:
		void initDriver(void);
	
	private:
		uint64_t aMqCbMem[ (osRtxMessageQueueCbSize + 7) / 8 ];
		uint64_t aMqMem[ (MICRO_WAVE_OVEN_MESSAGE_SIZE + 7) / 8 ];
	
		uint64_t qMutexMem[ (osRtxMutexCbSize + 7) / 8 ];
	
		osMessageQueueAttr_t sMqAttr;
		osMessageQueueId_t sMqId;
	
		osMutexAttr_t sMutexAttr;
		osMutexId_t sMutexId;
};






#endif

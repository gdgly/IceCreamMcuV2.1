#ifndef		__MICRO_WAVE_OVEN_UART_H
#define		__MICRO_WAVE_OVEN_UART_H

#include "stm32f4xx.h"
#include "Event/Event.h"
#include "Event/Sender.h"
#include "Event/Receiver.h"

class MicroWaveOvenUartEvent : public Event
{
	public:
		MicroWaveOvenUartEvent(void) : pMsg(NULL), nSize(0) {}
		
		inline void set(const uint8_t *msg, uint32_t size) {
			pMsg = msg;
			nSize = size;
		}
		
		inline const uint8_t *msg(void) {
			return pMsg;
		}
		
		inline uint32_t size(void) {
			return nSize;
		}
		
	private:
		const uint8_t *pMsg;
		uint32_t nSize;
};


#define MICRO_WAVE_OVEN_MESSAGE_OBJ_SIZE		sizeof (MicroWaveOvenUartEvent)
#define MICRO_WAVE_OVEN_MESSAGE_OBJ_NUMBER		10
#define MICRO_WAVE_OVEN_MESSAGE_SIZE			osRtxMessageQueueMemSize(MICRO_WAVE_OVEN_MESSAGE_OBJ_NUMBER, MICRO_WAVE_OVEN_MESSAGE_OBJ_SIZE)

class MicroWaveOvenUart : public Receiver, Sender
{
	public:
		inline static MicroWaveOvenUart *instance(void)
		{			
			static MicroWaveOvenUart uart;
			return &uart;
		}
	
	public:
		MicroWaveOvenUart(void);
		
		inline void write(uint8_t byte) 
		{
			while (0 == (USART3->SR & 0x80));
			USART3->DR = byte;
		}
		
		inline void write(const uint8_t *byteArray, uint32_t len) 
		{
			acquire();
			while (len --) 
			{
				write(*byteArray);
				byteArray ++;
			}
			release();
		}
		
		void write(const char *format, ...);
		
		inline MicroWaveOvenUart& operator<<(const char *str)
		{
			acquire();
			while (*str != '\0')
			{
				write((uint8_t) *str);
				str ++;
			}
			release();
			return *this;
		}

	private:
		void initDriver(void);
	
	private:
		uint64_t aMqMem[ (MICRO_WAVE_OVEN_MESSAGE_SIZE + 7) / 8 ];
};






#endif

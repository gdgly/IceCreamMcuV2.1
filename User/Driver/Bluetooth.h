#ifndef		__BLUETOOTH_H
#define		__BLUETOOTH_H

#include "Event/Receiver.h"
#include "Event/Sender.h"
#include "Event/Event.h"
#include "stm32f4xx.h"

class BluetoothEvent : public Event
{	
	public:
		BluetoothEvent(void) : pMsg(NULL), nMsgCount(0) {}
	
		inline void set(const uint8_t *msg, uint32_t count) {
			pMsg = msg;
			nMsgCount = count;
		}
		
		inline const uint8_t *msg(void) {
			return pMsg;
		}
		
		inline uint8_t size(void) {
			return nMsgCount;
		}
			
	private:
		const uint8_t *pMsg;
		uint32_t nMsgCount;
};

#define BLUETOOTH_MESSAGE_OBJ_SIZE			sizeof(BluetoothEvent)
#define BLUETOOTH_MESSAGE_OBJ_NUMBER		10
#define BLUETOOTH_MESSAGE_SIZE				osRtxMessageQueueMemSize(BLUETOOTH_MESSAGE_OBJ_NUMBER, BLUETOOTH_MESSAGE_OBJ_SIZE)


class Bluetooth : public Receiver, Sender
{
	public:
		static inline Bluetooth *instance(void) {
			static Bluetooth ble;
			return &ble;
		}
	
	public:
		Bluetooth(void);
		
		inline void write(const uint8_t *bytes, uint32_t length) 
		{
			acquire();
			while (length --)
			{
				write(*bytes);
				bytes ++;
			}
			release();
		}
	
	private:
		void initDriver(void);
		
		inline void write(uint8_t byte) 
		{
			while (0 == (USART2->SR & 0x80));
			USART2->DR = byte;
		}
	
	private:
		uint64_t aMqMem[ (BLUETOOTH_MESSAGE_SIZE + 7) / 8 ];
};

#endif

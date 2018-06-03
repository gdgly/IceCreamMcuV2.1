#ifndef		__BLUETOOTH_H
#define		__BLUETOOTH_H

#include "Event/Receiver.h"
#include "Event/Sender.h"
#include "Event/BluetoothEvent.h"
#include "stm32f4xx.h"

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
		
		void write(const uint8_t *bytes, uint32_t len);
	
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

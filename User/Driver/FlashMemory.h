#ifndef		__FLASH_MEMORY_H
#define		__FLASH_MEMORY_H

#include "Event/Sender.h"
#include "stm32f4xx.h"

class FlashMempry 
{
	public:
		static inline FlashMempry *instance(void) {
			static FlashMempry m;
			return &m;
		}
	
		void vReadData(uint32_t address, uint8_t *data, uint32_t size);
		void vWriteData(uint32_t address, const uint8_t *data, uint32_t size);
		
	private:
		FlashMempry(void);
		void initSpiInterface(void);
		uint8_t xTranslateByte(uint8_t byte);
		uint8_t xQueryStatus(void);
		void vWriteEnable(void);
		void vSectorEarse(uint32_t address);
		void vPageProgram(uint32_t address, const uint8_t *data, uint32_t size);
		inline void vCsLow(void) {
			GPIOB->BSRRH = 0x40;
		}
		
		inline void vCsHigh(void) {
			GPIOB->BSRRL = 0x40;
		}
		
};





#endif

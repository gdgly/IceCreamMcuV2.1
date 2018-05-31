#ifndef		__PICK_MOTO_H
#define		__PICK_MOTO_H

#include "Event/Sender.h"
#include "stm32f4xx.h"

class PickMoto : public Sender
{
	public:
		enum Dir {
			Up = 0x01,
			Down = 0x02,
			Brake = 0x03,
		};
	
	public:
		static inline PickMoto *instance(void) {
			static PickMoto pickMoto;
			return &pickMoto;
		}
	
		inline void vResetCounter(void) {
			TIM1->CNT = 0;
		}
		
		inline uint16_t xGetCounter(void) {
			return TIM1->CNT;
		}
		
		inline void vSetSpeed(uint16_t sp) {
			TIM11->CCR1 = sp;
		}
		
		inline void vSetDir(Dir dir)
		{
			switch (dir)
			{
				case Up:
					GPIOD->BSRRH = 0x4000;
					GPIOD->BSRRL = 0x8000;
					break;
				
				case Down:
					GPIOD->BSRRL = 0x4000;
					GPIOD->BSRRH = 0x8000;
					break;
				
				case Brake:
					GPIOD->BSRRH = 0xC000;
					break;
			}
		}
		
	private:
		PickMoto(void);
		void initMotoGpio(void);
		void initMotoDriver(void);
		void initCounterGpio(void);
		void initCounterDriver(void);
};



#endif

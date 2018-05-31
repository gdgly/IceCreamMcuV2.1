#ifndef		__ROBOT_ARM2_H
#define		__ROBOT_ARM2_H

#include "Event/Sender.h"
#include "stm32f4xx.h"

class RobotArm2 : public Sender
{
	public:
		enum Dir {
			CW = 0x01,
			CCW = 0x02,
			Brake = 0x03,
		};
	
	public:
		static inline RobotArm2 *instance(void) {
			static RobotArm2 instance;
			return &instance;
		}
	
		inline void vSetSpeed(uint16_t sp) {
			TIM3->CCR4 = sp;
		}
		
		int32_t xGetPosition(void) 
		{
			int32_t v = TIM5->CCR2 + nRawPosition;
			if (v > 1036) {
				return v - 1036;
			}
			if (v < 0) {
				return v + 1036;
			}
			return v;
		}
		
		inline void vSetDir(Dir dir)
		{
			switch (dir)
			{
				case CW:
					GPIOE->BSRRH = 0x20;
					GPIOE->BSRRL = 0x10;
					break;
				
				case CCW:
					GPIOE->BSRRL = 0x20;
					GPIOE->BSRRH = 0x10;
					break;
				
				case Brake:
					GPIOE->BSRRH = 0x30;
					break;
			}
		}
		
		inline void vSetPosition(void) {
			nRawPosition = 518 - TIM5->CCR2;
		}
		
	private:
		RobotArm2(void);
		void initMotoGpio(void);
		void initMotoDriver(void);
		void initCounterGpio(void);
		void initCounterDriver(void);
	
	private:
		int32_t nRawPosition;
};




#endif

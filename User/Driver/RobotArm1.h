#ifndef		__ROBOT_ARM1_H
#define		__ROBOT_ARM1_H

#include "Event/Sender.h"
#include "stm32f4xx.h"

/**
 * @brief 机械臂电机1和机械臂电机2的速度控制引脚都是TIM3的PWM输出引脚
 * 所以在此类中将会同时初始化这两个电机的速度控制引脚
 */

class RobotArm1 : public Sender
{
	public:
		enum Dir {
			CW = 0x01,
			CCW = 0x02,
			Brake = 0x03,
		};
	
	public:
		static inline RobotArm1 *instance(void) {
			static RobotArm1 r;
			return &r;
		}
		
		inline void vSetSpeed(uint16_t sp) {
			TIM3->CCR1 = sp;
		}
		
		int32_t xGetPosition(void) 
		{
			int32_t v = TIM2->CCR2 + nRawPosition;
			if (v < 0) {
				return v + 1036;
			} 
			if (v > 1036) {
				return v - 1036;
			}
			return v;
		}
		
		inline void vSetDir(Dir dir) 
		{
			switch (dir)
			{
				case CCW:
					GPIOE->BSRRH = 0x04;
					GPIOE->BSRRL = 0x08;
					break;
				
				case CW:
					GPIOE->BSRRL = 0x04;
					GPIOE->BSRRH = 0x08;
					break;
				
				case Brake:
					GPIOE->BSRRH = 0x0C;
					break;
			}
		}
		
		inline void vSetPosition(void) {
			nRawPosition = 518 - TIM2->CCR2;
		}
		
		void runTo(const uint16_t position, const uint16_t speed);
		
	private:
		RobotArm1(void);
		void initMotoGpio(void);
		void initMotoDriver(void);
		void initCounterGpio(void);
		void initCounterDriver(void);
	
	private:
		int32_t nRawPosition;
};





#endif

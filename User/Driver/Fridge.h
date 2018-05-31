#ifndef		__REF_MOTO_H
#define		__REF_MOTO_H

#include "stm32f4xx.h"
#include "Event/Sender.h"

/**
 * @brief 冰箱门管理类
 */
class Fridge : public Sender
{
	public:
		enum Dir {
			Up = 0x01,
			Down = 0x02,
			Brake = 0x03,
		};
	
	public:
		static inline Fridge *instance(void) {
			static Fridge fridge;
			return &fridge;
		}
		
		/**
		 * @brief 复位冰箱门电机的编码器计数器
		 */
		inline void vResetCounter(void) {
			TIM4->CNT = 0;
		}
		
		/**
		 * @brief 获取冰箱门电机编码器的计数值
		 */
		inline uint16_t vGetCouner(void) {
			return TIM4->CNT;
		}
		
		/**
		 * @brief 设置冰箱门电机的转速 sp 转速百分比
		 */
		inline void vSetSpeed(uint16_t sp) {
			TIM9->CCR2 = sp;
		}
		
		inline void vSerDir(Dir dir) 
		{
			switch (dir)
			{
				case Up:
					GPIOE->BSRRL = 0x40;
					GPIOE->BSRRH = 0x80;
					break;
				case Down:
					GPIOE->BSRRH = 0x40;
					GPIOE->BSRRL = 0x80;
					break;
				case Brake:
					GPIOE->BSRRH = 0xC0;
					break;
			}
		}
		
	private:
		Fridge(void);
		void initMotoGpio(void);
		void initMotoDriver(void);
		void initCounterGpio(void);
		void initCounterDriver(void);
};

#endif

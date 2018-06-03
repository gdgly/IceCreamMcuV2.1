#include "Driver/RobotArm2.h"



RobotArm2::RobotArm2(void) : Sender("RobotArm2")
{
	initMotoGpio();
	initMotoDriver();
	initCounterGpio();
	initCounterDriver();
	vSetDir(Brake);
}

void RobotArm2::runTo(const uint16_t position, const uint16_t speed)
{
	uint16_t v;
	vSetSpeed(speed);
	while (true)
	{
		v = xGetPosition();
		if (position > v) {
			vSetDir(CW);
		} else if (position < v) {
			vSetDir(CCW);
		} else {
			vSetDir(Brake);
			return;
		}
		osDelay(20);
	}
}


void RobotArm2::initCounterDriver(void)
{
	RCC->APB1ENR |= 0x08;
	
	TIM5->CR1 = 0x00;
	TIM5->CR2 = 0x00;
	TIM5->PSC = 84 - 1;
	TIM5->ARR = 0xFFFFFFFF;
	TIM5->CCMR1 = 0x0201;
	TIM5->CCER = 0x31;
	TIM5->SMCR = 0x54;
	TIM5->CR1 = 0x01;
	TIM5->EGR = 0x01;
}

/**
 * @brief Timer5 CH1 <-> PA0 <-> AF2 磁编码器2
 */
void RobotArm2::initCounterGpio(void)
{
	RCC->AHB1ENR |= 0x01;
	
	GPIOA->MODER &= ~0x03;
	GPIOA->MODER |= 0x02;
	GPIOA->PUPDR &= ~0x03;
	GPIOA->PUPDR |= 0x01;
	GPIOA->OSPEEDR |= 0x03;
	GPIOA->OTYPER &= ~0x01;
	GPIOA->AFR[0] &= ~0x0F;
	GPIOA->AFR[0] |= 0x02;
}

void RobotArm2::initMotoDriver(void) 
{
	
}

/**
 * @brief 初始化机械臂电机2的控制引脚
 * PE4 <-> OUT
 * PE5 <-> OUT
 */
void RobotArm2::initMotoGpio(void)
{
	RCC->AHB1ENR |= 0x10;
	
	GPIOE->MODER &= ~0xF00;
	GPIOE->MODER |= 0x500;
	GPIOE->PUPDR &= ~0xF00;
	GPIOE->OSPEEDR |= 0xF00;
	GPIOE->OTYPER &= ~0x30;
}








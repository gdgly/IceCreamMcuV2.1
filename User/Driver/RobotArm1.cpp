#include "Driver/RobotArm1.h"


RobotArm1::RobotArm1(void) : Sender("RobotArm1")
{
	initMotoGpio();
	initMotoDriver();
	initCounterGpio();
	initCounterDriver();
	vSetDir(Brake);
}

/**
 * @brief 初始化机械臂电机1编码器输入引脚
 * Timer2 CH1 <-> PA15 PWM输入模式
 */
void RobotArm1::initCounterDriver(void)
{
	RCC->APB1ENR |= 0x01;
	
	TIM2->CR1 = 0x00;
	TIM2->CR2 = 0x00;
	TIM2->PSC = 84 - 1;
	TIM2->ARR = 0xFFFFFFFF;
	TIM2->CCMR1 = 0x0201;
	TIM2->CCER = 0x0031;
	TIM2->SMCR = 0x54;
	TIM2->CR1 = 0x01;
	TIM2->EGR = 0x01;
}

/**
 * @brief 初始化机械臂电机1编码器输入引脚
 * Timer2 CH1 <-> PA15 <-> AF1 磁编码器1
 */
void RobotArm1::initCounterGpio(void)
{
	RCC->AHB1ENR |= 0x01; // Enable GPIOA
	
	GPIOA->MODER &= ~0xC0000000;
	GPIOA->MODER |= 0x80000000;
	GPIOA->PUPDR &= ~0xC0000000;
	GPIOA->PUPDR |= 0x40000000;
	GPIOA->OSPEEDR |= 0xC0000000;
	GPIOA->OTYPER &= ~0x8000;
	GPIOA->AFR[1] &= ~0xF0000000;
	GPIOA->AFR[1] |= 0x10000000;
}

/**
 * @brief 初始化机械臂电机1和机械臂电机2(仅仅速度控制引脚)
 * PC6 <-> TIM3_CH1 AF2 频率500Hz
 * PC9 <-> TIM3_CH4 AF2 频率500Hz
 */
void RobotArm1::initMotoDriver(void)
{
	RCC->APB1ENR |= 0x02;
	
	TIM3->CR1 = 0x00;
	TIM3->CR2 = 0x00;
	TIM3->PSC = 84 * 20 - 1;
	TIM3->ARR = 100 - 1;
	TIM3->CCR1 = 100;
	TIM3->CCR4 = 100;
	TIM3->CCMR1 = 0x0070;
	TIM3->CCMR2 = 0x7000;
	TIM3->CCER = 0x1001;
	TIM3->CR1 = 0x01;
	TIM3->EGR = 0x01;
}


/**
 * @brief 初始化机械臂电机1和机械臂电机2(仅仅速度控制引脚)
 * PC6 <-> TIM3_CH1 AF2
 * PC9 <-> TIM3_CH4 AF2
 * PE2 <-> OUT
 * PE3 <-> OUT
 */
void RobotArm1::initMotoGpio(void)
{
	RCC->AHB1ENR |= 0x14;
	
	GPIOC->MODER &= ~0xC3000;
	GPIOC->MODER |= 0x82000;
	GPIOC->PUPDR &= ~0xC3000;
	GPIOC->OSPEEDR |= 0xC3000;
	GPIOC->OTYPER &= ~0x240;
	GPIOC->AFR[0] &= ~0x0F000000;
	GPIOC->AFR[0] |= 0x02000000;
	GPIOC->AFR[1] &= ~0xF0;
	GPIOC->AFR[1] |= 0x20;
	
	GPIOE->MODER &= ~0xF0;
	GPIOE->MODER |= 0x50;
	GPIOE->PUPDR &= ~0xF0;
	GPIOE->OSPEEDR |= 0xF0;
	GPIOE->OTYPER &= ~0xC0;
}






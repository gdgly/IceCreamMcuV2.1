#include "Driver/Fridge.h"



Fridge::Fridge(void) : Sender("Fridge")
{
	initMotoGpio();
	initMotoDriver();
	initCounterGpio();
	initCounterDriver();
	vSerDir(Brake);
}

/**
 * @brief 冰箱门电机控制引脚
 * PA3 <-> TIM9_CH2 <-> AF3
 * PE6 <-> OUT
 * PE7 <-> OUT
 */
void Fridge::initMotoGpio(void)
{
	RCC->AHB1ENR |= 0x01 | 0x10;
	
	GPIOA->MODER &= ~0xC0;
	GPIOA->MODER |= 0x20;
	GPIOA->PUPDR &= ~0xC0;
	GPIOA->OSPEEDR |= 0xC0;
	GPIOA->OTYPER &= ~0x08;
	GPIOA->AFR[0] &= ~0xF000;
	GPIOA->AFR[0] |= 0x3000;
	
	GPIOE->MODER &= ~0xF000;
	GPIOE->MODER |= 0x5000;
	GPIOE->PUPDR &= ~0xF000;
	GPIOE->OSPEEDR |= 0xF000;
	GPIOE->OTYPER &= ~0xC0;
}

/**
 * @brief 冰箱门电机速度控制初始化
 * TIM9_CH2 <-> PWM = 500k
 */
void Fridge::initMotoDriver(void)
{
	RCC->APB2ENR |= 0x10000; // Enable TIM9
	
	TIM9->CR1 = 0x00;
	TIM9->CR2 = 0x00;
	TIM9->PSC = 168 * 20 - 1;
	TIM9->ARR = 100 - 1;
	TIM9->CCR2 = 100;
	TIM9->CCMR1 = 0x7000;
	TIM9->CCER = 0x0010;
	TIM9->CR1 = 0x01;
	TIM9->EGR = 0x01;
}

/**
 * @brief 冰箱门电机计数器初始化
 * PD12 <-> TIM4_CH1 <-> AF2
 */
void Fridge::initCounterGpio(void)
{
	RCC->AHB1ENR |= 0x08;
	
	GPIOD->MODER &= ~0x3000000;
	GPIOD->MODER |= 0x2000000;
	GPIOD->PUPDR &= ~0x3000000;
	GPIOD->PUPDR |= 0x1000000;
	GPIOD->OSPEEDR |= 0x3000000;
	GPIOD->OTYPER &= ~0x1000;
	GPIOD->AFR[1] &= ~0xF0000;
	GPIOD->AFR[1] |= 0x20000;
}

/**
 * @brief 冰箱门电机计数器设置
 * TIM4_CH1 工作在PWM输入模式
 */
void Fridge::initCounterDriver(void)
{
	RCC->APB1ENR |= 0x04;
	
	TIM4->CR1 = 0x00;
	TIM4->CR2 = 0x00;
	TIM4->SMCR = 0x57;
	TIM4->CCMR1 = 0x01;
	TIM4->CCER &= ~0x0A;
	TIM4->CR1 = 0x01;
}







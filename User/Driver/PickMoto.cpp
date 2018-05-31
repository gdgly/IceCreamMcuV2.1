#include "Driver/PickMoto.h"



PickMoto::PickMoto(void) : Sender("PickMoto")
{
	initMotoGpio();
	initMotoDriver();
	initCounterGpio();
	initCounterDriver();
	vSetDir(Brake);
}

/**
 * @brief 初始化取货电机的编码器计数引脚
 * TIM1_CH1
 */
void PickMoto::initCounterDriver(void)
{
	RCC->APB2ENR   |= 		0x01;
	
	TIM1->CR1 		= 		0x00;
	TIM1->CR2 		= 		0x00;
	TIM1->SMCR 		= 		0x57;
	TIM1->CCMR1 	= 		0x01;
	TIM1->CCER 	   &= 	   ~0x0A;
	TIM1->CR1 		= 		0x01;
}

/**
 * @brief 初始化取货电机的编码器计数引脚
 * PE9 <-> TIM1_CH1 <-> AF1
 */
void PickMoto::initCounterGpio(void)
{
	RCC->AHB1ENR 	|= 		 0x10; // Enable GPIOE
	
	GPIOE->MODER	&= 		~0xC0000;
	GPIOE->MODER 	|= 		 0x80000;
	GPIOE->PUPDR 	&= 		~0xC0000;
	GPIOE->PUPDR 	|= 		 0x40000;
	GPIOE->OSPEEDR 	|= 		 0xC0000;
	GPIOE->OTYPER 	&= 	 	~0x200;
	GPIOE->AFR[1] 	&= 		~0xF0;
	GPIOE->AFR[1] 	|= 		 0x10;
}

/**
 * @brief 初始化取货电机的控制引脚
 * PB9 <-> TIM11_CH1 <-> AF3
 * PD14 <-> OUT
 * PD15 <-> OUT
 */
void PickMoto::initMotoGpio(void)
{
	RCC->AHB1ENR |= 0x0A;
	
	GPIOB->MODER &= ~0xC0000;
	GPIOB->MODER |= 0x80000;
	GPIOB->PUPDR &= ~0xC0000;
	GPIOB->OSPEEDR |= 0xC0000;
	GPIOB->OTYPER &= ~0x200;
	GPIOB->AFR[1] &= ~0xF0;
	GPIOB->AFR[1] |= 0x30;
	
	GPIOD->MODER &= ~0xF0000000;
	GPIOD->MODER |= 0xA0000000;
	GPIOD->PUPDR &= ~0xF0000000;
	GPIOD->OSPEEDR |= 0xF0000000;
	GPIOD->OTYPER &= ~0xC000;
}

/**
 * @brief 初始化PWM输出引脚
 * PWM频率=500
 */
void PickMoto::initMotoDriver(void)
{
	RCC->APB2ENR |= 0x40000; // Enable TIM11
	
	TIM11->CR1 = 0x00;
	TIM11->CR2 = 0x00;
	TIM11->PSC = 168 * 20 - 1;
	TIM11->ARR = 100 - 1;
	TIM11->CR1 = 100;
	TIM11->CCMR1 = 0x0070;
	TIM11->CCER = 0x0001;
	TIM11->CR1 = 0x01;
	TIM11->EGR = 0x01;
}











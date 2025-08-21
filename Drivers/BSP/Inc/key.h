/* 按键驱动程序 */

#ifndef __KEY_H
#define __KEY_H

#include "led.h"
#include "delay.h"
#include "usart.h"

/* 引脚和时钟 */
#define KEY0_EXTI_PORT          GPIOH
#define KEY0_EXTI_Pin           GPIO_PIN_3
#define KEY0_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while(0)
#define KEY0_EXTI_IRQn          EXTI3_IRQn
#define KEY0_EXTI_IRQHandler    EXTI3_IRQHandler
#define KEY0                    HAL_GPIO_ReadPin(KEY0_EXTI_PORT, KEY0_EXTI_Pin)

#define KEY1_EXTI_PORT          GPIOH
#define KEY1_EXTI_Pin           GPIO_PIN_2
#define KEY1_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while(0)
#define KEY1_EXTI_IRQn          EXTI2_IRQn
#define KEY1_EXTI_IRQHandler    EXTI2_IRQHandler
#define KEY1                    HAL_GPIO_ReadPin(KEY1_EXTI_PORT, KEY1_EXTI_Pin)

#define KEY2_EXTI_PORT          GPIOC
#define KEY2_EXTI_Pin           GPIO_PIN_13
#define KEY2_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();} while(0)
#define KEY2_EXTI_IRQn          EXTI15_10_IRQn
#define KEY2_EXTI_IRQHandler    EXTI15_10_IRQHandler
#define KEY2                    HAL_GPIO_ReadPin(KEY2_EXTI_PORT, KEY2_EXTI_Pin)

#define KEYU_EXTI_PORT          GPIOA
#define KEYU_EXTI_Pin           GPIO_PIN_0
#define KEYU_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOA_CLK_ENABLE();} while(0)
#define KEYU_EXTI_IRQn          EXTI0_IRQn
#define KEYU_EXTI_IRQHandler    EXTI0_IRQHandler
#define KEYU                    HAL_GPIO_ReadPin(KEYU_EXTI_PORT, KEYU_EXTI_Pin)

/* 变量声明 */
extern GPIO_InitTypeDef key_handler;
extern uint8_t exti[USART_UX_EXTI_SIZE];   /* 你好STM32（UTF-8）*/

/* 初始化EXTI */
void key_init(void);

#endif
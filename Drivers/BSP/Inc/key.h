/* 按键驱动程序 */

#ifndef __KEY_H
#define __KEY_H

#include "led.h"
#include "delay.h"
#include "beep.h"

/* 引脚和时钟 */
#define KEY0_EXTI_PORT          GPIOE
#define KEY0_EXTI_Pin           GPIO_PIN_4
#define KEY0_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while(0)
#define KEY0_EXTI_IRQn          EXTI4_IRQn        /* KEY0中断号 */
#define KEY0_EXTI_IRQHandler    EXTI4_IRQHandler  /* KEY0中断服务函数 */
#define KEY0                    HAL_GPIO_ReadPin(KEY0_EXTI_PORT, KEY0_EXTI_Pin)

#define KEY1_EXTI_PORT          GPIOE
#define KEY1_EXTI_Pin           GPIO_PIN_3
#define KEY1_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while(0)
#define KEY1_EXTI_IRQn          EXTI3_IRQn
#define KEY1_EXTI_IRQHandler    EXTI3_IRQHandler
#define KEY1                    HAL_GPIO_ReadPin(KEY1_EXTI_PORT, KEY1_EXTI_Pin)

#define KEY2_EXTI_PORT          GPIOE
#define KEY2_EXTI_Pin           GPIO_PIN_2
#define KEY2_EXTI_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while(0)
#define KEY2_EXTI_IRQn          EXTI2_IRQn
#define KEY2_EXTI_IRQHandler    EXTI2_IRQHandler
#define KEY2                    HAL_GPIO_ReadPin(KEY2_EXTI_PORT, KEY2_EXTI_Pin)

/* 初始化EXTI */
void key_init(void);

#endif
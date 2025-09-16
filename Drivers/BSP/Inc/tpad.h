/* 电容触摸按键驱动 */

#ifndef __TPAD_H
#define __TPAD_H

#include "sys.h"

/* 引脚和定时器 */
#define TPAD_GPIO_PORT           GPIOA
#define TPAD_GPIO_PIN            GPIO_PIN_5
#define TPAD_GPIO_AF             GPIO_AF1_TIM2
#define TPAD_TIME                TIM2
#define TPAD_TIME_CHANNEL        TIM_CHANNEL_1
#define TPAD_TIME_IRQn           TIM2_IRQn
#define TPAD_TIME_IRQHandler     TIM2_IRQHandler
#define TPAD_GPIO_CLK_ENABLE()   do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define TPAD_TIME_CLK_ENABLE()   do {__HAL_RCC_TIM2_CLK_ENABLE();}  while (0)

/* 电容按键初始化 */
void tpad_init(uint16_t div);

/* 变量声明 */
extern uint16_t          ctor_coun;
extern TIM_HandleTypeDef tpad_time_handler;

#endif
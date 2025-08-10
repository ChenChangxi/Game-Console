/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "led.h"

/* 基本定时器 */
#define BASE_TIME                TIM7
#define BASE_TIME_IRQn           TIM7_IRQn
#define BASE_TIME_IRQHandler     TIM7_IRQHandler
#define BASE_TIME_CLK_ENABLE()   do {__HAL_RCC_TIM7_CLK_ENABLE();} while (0)

/* 定时器初始化 */
void base_time_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern TIM_HandleTypeDef base_time_handler;

#endif
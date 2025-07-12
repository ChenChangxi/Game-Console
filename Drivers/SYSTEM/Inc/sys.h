/* 系统初始化（时钟/中断/GPIO等）*/

#ifndef __SYS_H
#define __SYS_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

/* 配置STM32F407时钟树 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);

#endif
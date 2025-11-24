/* 系统初始化 */

#ifndef __SYS_H
#define __SYS_H

#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_ll_gpio.h"

/* 配置STM32H743时钟树 */
void sys_stm32_clock_init(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq);

/* 开启Cache */
void sys_cache_enable(void);

/* DCache与SRAM同步 */
void sys_cache_sram_sync(uint32_t addr, uint32_t size);

/* 变量声明 */
extern RCC_OscInitTypeDef       osc_init;
extern RCC_ClkInitTypeDef       clk_init;
extern RCC_PeriphCLKInitTypeDef per_init;

#endif
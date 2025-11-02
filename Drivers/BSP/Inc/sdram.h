/* SDRAM驱动 */

#ifndef __SDRAM_H
#define __SDRAM_H

#include "sys.h"
#include "delay.h"

/* SDRAM命令引脚 */
#define SDRAM_CAS_PORT          GPIOG           /* 行选通 */
#define SDRAM_RAS_PORT          GPIOF           /* 列选通 */
#define SDRAM_WER_PORT          GPIOC           /* 读写 */
#define SDRAM_CSE_PORT          GPIOC           /* 片选 */
#define SDRAM_BAN_PORT          GPIOG           /* 区号 */
#define SDRAM_CLK_PORT          GPIOG           /* 同步时钟 */
#define SDRAM_CKE_PORT          GPIOC           /* 工作/休眠 */
#define SDRAM_NBL_PORT          GPIOE           /* 掩码 */

#define SDRAM_CAS_PIN           GPIO_PIN_15
#define SDRAM_RAS_PIN           GPIO_PIN_11
#define SDRAM_WER_PIN           GPIO_PIN_0
#define SDRAM_CSE_PIN           GPIO_PIN_2
#define SDRAM_BAN_PIN           GPIO_PIN_4 | GPIO_PIN_5
#define SDRAM_CLK_PIN           GPIO_PIN_8
#define SDRAM_CKE_PIN           GPIO_PIN_3
#define SDRAM_NBL_PIN           GPIO_PIN_0 | GPIO_PIN_1

#define SDRAM_AF                GPIO_AF12_FMC

#define SDRAM_CAS_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define SDRAM_RAS_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)
#define SDRAM_WER_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();} while (0)
#define SDRAM_CSE_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();} while (0)
#define SDRAM_BAN_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define SDRAM_CLK_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define SDRAM_CKE_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();} while (0)
#define SDRAM_NBL_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while (0)

/* SDRAM初始化 */
void sdram_init(void);

/* W9825G6KH-6初始化 */
void w9825g6kh6_init(void);

/* 变量声明 */
extern SDRAM_HandleTypeDef      sdram_init_handler;
extern FMC_SDRAM_TimingTypeDef  sdram_time_handler;
extern FMC_SDRAM_CommandTypeDef sdram_comd_handler;

#endif
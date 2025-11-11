/* NAND FLASH驱动 */

#ifndef __NAND_FLASH_H
#define __NAND_FLASH_H

#include "sys.h"

/* 引脚和时钟 */
#define NAND_NWE_PORT          GPIOD           /* 读 */
#define NAND_NOE_PORT          GPIOD           /* 写 */
#define NAND_NCE_PORT          GPIOG           /* 片选 */
#define NAND_NWA_PORT          GPIOD           /* 等待 */

#define NAND_NWE_PIN           GPIO_PIN_5
#define NAND_NOE_PIN           GPIO_PIN_4
#define NAND_NCE_PIN           GPIO_PIN_9
#define NAND_NWA_PIN           GPIO_PIN_6

#define NAND_AF                GPIO_AF12_FMC

#define NAND_NWE_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define NAND_NOE_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define NAND_NCE_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define NAND_NWA_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)

/* 初始化NAND FLASH */
void nand_init(void);

/* 变量声明 */
extern NAND_HandleTypeDef         nand_init_handler;
extern FMC_NAND_PCC_TimingTypeDef nand_time_handler;

#endif
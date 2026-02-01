/* SD Card驱动程序 */

#ifndef __SD_CARD_H
#define __SD_CARD_H

#include "sys.h"

/* SDIO引脚 */
#define SD                   SDMMC1
#define SD_IOx_PORT          GPIOC
#define SD_CMD_PORT          GPIOD
#define SD_CLK_PORT          GPIOC
#define SD_IOx_PIN           GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
#define SD_CMD_PIN           GPIO_PIN_2
#define SD_CLK_PIN           GPIO_PIN_12
#define SD_AF                GPIO_AF12_SDMMC1
#define SD_CLK_ENABLE()      do {__HAL_RCC_SDMMC1_CLK_ENABLE();} while (0)
#define SD_IOx_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();}  while (0)
#define SD_CMD_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();}  while (0)
#define SD_CLK_CLK_ENABLE()  do {__HAL_RCC_GPIOC_CLK_ENABLE();}  while (0)

/* SD卡初始化 */
void sd_init(void);

/* 变量声明 */
extern SD_HandleTypeDef sd_init_handler;

#endif
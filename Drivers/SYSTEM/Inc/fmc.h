/* FMC数据和地址总线 */

#ifndef __FMC_H
#define __FMC_H

#include "sys.h"

/* FMC地址和数据引脚 */
#define FMC_DATA_PORT_X          GPIOD
#define FMC_DATA_PORT_Y          GPIOE
#define FMC_ADDR_PORT_X          GPIOF
#define FMC_ADDR_PORT_Y          GPIOG
#define FMC_DATA_PIN_X           GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | \
                                 GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define FMC_DATA_PIN_Y           GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | \
                                 GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
                                 GPIO_PIN_12 | GPIO_PIN_13 |  GPIO_PIN_14 |  GPIO_PIN_15
#define FMC_ADDR_PIN_X           GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | \
                                 GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define FMC_ADDR_PIN_Y           GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | \
                                 GPIO_PIN_5 | GPIO_PIN_13 | GPIO_PIN_14
#define FMC_AF                   GPIO_AF12_FMC
#define FMC_CLK_ENABLE()         do {__HAL_RCC_FMC_CLK_ENABLE();}   while (0)
#define FMC_DATA_X_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define FMC_DATA_Y_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while (0)
#define FMC_ADDR_X_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)
#define FMC_ADDR_Y_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)

/* FMC初始化 */
void fmc_init(void);

#endif
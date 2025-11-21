/* LTDC驱动程序 */

#ifndef __LTDC_H
#define __LTDC_H

#include "sys.h"

/* LTDC外设 */
#define RGB_AF                GPIO_AF14_LTDC
#define RGB_MODE              0
#define RGB_CLK_ENABLE()      do {__HAL_RCC_LTDC_CLK_ENABLE();} while (0)

/* LTDC命令引脚 */
#define RGB_DAE_PORT          GPIOF
#define RGB_HSN_PORT          GPIOI
#define RGB_VSN_PORT          GPIOI
#define RGB_CLK_PORT          GPIOG
#define RGB_DAE_PIN           GPIO_PIN_10
#define RGB_HSN_PIN           GPIO_PIN_10
#define RGB_VSN_PIN           GPIO_PIN_9
#define RGB_CLK_PIN           GPIO_PIN_7
#define RGB_DAE_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)
#define RGB_HSN_CLK_ENABLE()  do {__HAL_RCC_GPIOI_CLK_ENABLE();} while (0)
#define RGB_VSN_CLK_ENABLE()  do {__HAL_RCC_GPIOI_CLK_ENABLE();} while (0)
#define RGB_CLK_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)

/* LTDC数据引脚 */
#define RGB_RED_PORT          GPIOH
#define RGB_GEN_PORT          GPIOI
#define RGB_BUE_PORT          GPIOG
#define RGB_RED_PIN           GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | \
                              GPIO_PIN_14 | GPIO_PIN_15
#define RGB_GEN_PIN           GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | \
                              GPIO_PIN_6 | GPIO_PIN_7
#define RGB_BUE_PIN           GPIO_PIN_6 | GPIO_PIN_11
#define RGB_RED_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while (0)
#define RGB_GEN_CLK_ENABLE()  do {__HAL_RCC_GPIOI_CLK_ENABLE();} while (0)
#define RGB_BUE_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)

/* LTDC初始化 */
void rgb_init(void);

/* 屏幕描点 */
void rgb_draw_dot(uint16_t x, uint16_t y, uint16_t dot);

/* 屏幕读点 */
uint16_t rgb_show_dot(uint16_t x, uint16_t y);

/* 变量声明 */
extern LTDC_HandleTypeDef rgb_init_handler;
extern LTDC_LayerCfgTypeDef rgb_layer_handler;

#endif
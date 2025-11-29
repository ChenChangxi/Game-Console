/* LTDC驱动程序 */

#ifndef __LTDC_H
#define __LTDC_H

#include "sys.h"

/* LTDC外设 */
#define RGB_AF                GPIO_AF14_LTDC
#define RGB_MODE              1   /* 0为横屏，1为竖屏 */
#define RGB_WIDTH             120
#define RGB_HEIGHT            200
#define RGB_CLK_ENABLE()      do {__HAL_RCC_LTDC_CLK_ENABLE();} while (0)
#define RGB_DMA_CLK_ENABLE()  do {__HAL_RCC_DMA2D_CLK_ENABLE();} while (0)

/* LTDC命令引脚 */
#define RGB_DAE_PORT          GPIOF
#define RGB_HSN_PORT          GPIOI
#define RGB_VSN_PORT          GPIOI
#define RGB_CLK_PORT          GPIOG
#define RGB_BLN_PORT          GPIOB
#define RGB_DAE_PIN           GPIO_PIN_10
#define RGB_HSN_PIN           GPIO_PIN_10
#define RGB_VSN_PIN           GPIO_PIN_9
#define RGB_CLK_PIN           GPIO_PIN_7
#define RGB_BLN_PIN           GPIO_PIN_5
#define RGB_DAE_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)
#define RGB_HSN_CLK_ENABLE()  do {__HAL_RCC_GPIOI_CLK_ENABLE();} while (0)
#define RGB_VSN_CLK_ENABLE()  do {__HAL_RCC_GPIOI_CLK_ENABLE();} while (0)
#define RGB_CLK_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define RGB_BLN_CLK_ENABLE()  do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

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

/* RGB背光控制 */
#define RGB_BLN(x) \
    do {HAL_GPIO_WritePin(RGB_BLN_PORT, RGB_BLN_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* LTDC初始化 */
void rgb_init(void);

/* 屏幕描点 */
void rgb_draw_dot(uint16_t x, uint16_t y, uint16_t dot);

/* 屏幕读点 */
uint16_t rgb_show_dot(uint16_t x, uint16_t y);

/* 屏幕区域 */
void rgb_reco_area(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye);

/* 屏幕填充（DMA2D由R到M）*/
void rgb_draw_area(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t area);

/* 屏幕画图（DMA2D由M到M）*/
void rgb_draw_picture(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t *picture);

/* 变量声明 */
extern uint32_t             addr, size, offs;
extern uint16_t             rgb_ram[RGB_HEIGHT][RGB_WIDTH] __attribute__((section(".sdram")));
extern LTDC_HandleTypeDef   rgb_init_handler;
extern LTDC_LayerCfgTypeDef rgb_layer_handler;

#endif
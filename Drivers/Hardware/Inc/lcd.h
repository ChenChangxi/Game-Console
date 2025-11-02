/* LCD驱动程序 */

#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "delay.h"

/* LCD命令引脚 */
#define LCD_CON_PORT          GPIOD
#define LCD_BLN_PORT          GPIOB
#define LCD_CON_PIN           GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_13
#define LCD_BLN_PIN           GPIO_PIN_5
#define LCD_AF                GPIO_AF12_FMC
#define LCD_CON_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define LCD_BLN_CLK_ENABLE()  do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

/* LCD背光控制 */
#define LCD_BLN(x) \
    do {HAL_GPIO_WritePin(LCD_BLN_PORT, LCD_BLN_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* LCD数据命令 */
#define LCD ((LCD_STA *) LCD_BASE)
#define LCD_BASE (uint32_t)(0x60080000 - 1<<1)
typedef struct {uint16_t CMD;uint16_t DAT;} LCD_STA;

/* LCD屏幕参数 */
typedef struct {uint16_t w;uint16_t h;uint16_t i;uint16_t s;uint16_t g;uint16_t x;uint16_t y;} LCD_CON;

/* NT35510初始化 */
void nt35510_init(void);

/* LCD初始化 */
void lcd_init(void);

/* 屏幕坐标 */
void lcd_set_cursor(uint16_t x, uint16_t y);

/* 屏幕描点 */
void lcd_draw_dot(uint16_t x, uint16_t y, uint16_t dot);

/* 屏幕读点 */
uint16_t lcd_show_dot(uint16_t x, uint16_t y);

/* 变量声明 */
extern LCD_CON                   lcd;
extern SRAM_HandleTypeDef        lcd_init_handler;
extern FMC_NORSRAM_TimingTypeDef lcd_time_handler, lex_time_handler;

#endif
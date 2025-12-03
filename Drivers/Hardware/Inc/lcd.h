/* LCD驱动程序 */

#ifndef __LCD_H
#define __LCD_H

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
#define LCD_BASE (uint32_t)(0x60080000 - (1<<1))
typedef struct {volatile uint16_t CMD;volatile uint16_t DAT;} LCD_STA;

/* LCD常用颜色 */
#define WHITE           0xFFFF      /* 白色 */
#define BLACK           0x0000      /* 黑色 */
#define RED             0xF800      /* 红色 */
#define GREEN           0x07E0      /* 绿色 */
#define BLUE            0x001F      /* 蓝色 */
#define MAGENTA         0XF81F      /* 品红色/紫红色 = BLUE + RED */
#define YELLOW          0XFFE0      /* 黄色 = GREEN + RED */
#define CYAN            0X07FF      /* 青色 = GREEN + BLUE */

/* LCD非常用颜色 */
#define BROWN           0XBC40      /* 棕色 */
#define BRRED           0XFC07      /* 棕红色 */
#define GRAY            0X8430      /* 灰色 */
#define DARKBLUE        0X01CF      /* 深蓝色 */
#define LIGHTBLUE       0X7D7C      /* 浅蓝色 */
#define GRAYBLUE        0X5458      /* 灰蓝色 */
#define LIGHTGREEN      0X841F      /* 浅绿色 */
#define LGRAY           0XC618      /* 浅灰色(PANNEL),窗体背景色 */
#define LGRAYBLUE       0XA651      /* 浅灰蓝色(中间层颜色) */
#define LBBLUE          0X2B12      /* 浅棕蓝色(选择条目的反色) */

/* ILI9806G初始化 */
void ili9806g_init(void);

/* LCD初始化 */
void lcd_init(void);

/* 屏幕坐标 */
void lcd_set_cursor(uint16_t x, uint16_t y);

/* 屏幕描点 */
void lcd_draw_dot(uint16_t x, uint16_t y, uint16_t dot);

/* 屏幕读点 */
uint16_t lcd_show_dot(uint16_t x, uint16_t y);

/* 变量声明 */
extern SRAM_HandleTypeDef        lcd_init_handler;
extern FMC_NORSRAM_TimingTypeDef lcd_time_handler, lex_time_handler;

#endif
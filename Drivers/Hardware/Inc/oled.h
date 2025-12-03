/* OLED驱动程序 */

#ifndef __OLED_H
#define __OLED_H

#include "delay.h"

/* 8080并口引脚 */
#define OLED_CON_PORT          GPIOE
#define OLED_INS_PORT          GPIOB
#define OLED_CON_PIN           GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
#define OLED_INS_PIN           GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | \
                               GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9
#define OLED_CON_CLK_ENABLE()  do {__HAL_RCC_GPIOE_CLK_ENABLE();} while (0)
#define OLED_INS_CLK_ENABLE()  do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

/* 8080并口读写 */
#define OLED_CON(CON,STE) \
    do {HAL_GPIO_WritePin(OLED_CON_PORT, CON, STE ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)
#define OLED_INS(INS) \
    do {OLED_INS_PORT -> ODR = (OLED_INS_PORT -> ODR & ~(0x00ff<<2)) | ((0x00ff & INS)<<2);} while (0)

/* SSD1306指令 */
#define OLED_ROW           0xb0        /* 页基地址 */
#define OLED_COL_MSB       0x10        /* 行高位基地址 */
#define OLED_COL_LSB       0x00        /* 行低位基地址 */

/* 枚举定义 */
typedef enum {CMD, DAT} OLED_Type;
typedef enum {
    CS = GPIO_PIN_2, DC = GPIO_PIN_3, RW = GPIO_PIN_4, RD = GPIO_PIN_5, RS = GPIO_PIN_6
} OLED_CON_Type;

/* OLED初始化 */
void oled_init(void);

/* SSD1306初始化 */
void ssd1306_init(void);

/* 写指令/数据 */
void oled_write_byte(uint8_t con, OLED_Type typ);

/* 屏幕描点 */
void oled_draw_dot(uint8_t x, uint8_t y, uint8_t dot);

/* 刷新显存到屏幕 */
void oled_refresh_ram(void);

/* 变量声明 */
extern uint8_t          oled_ram[128][8];
extern GPIO_InitTypeDef oled_handler;

#endif
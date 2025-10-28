/* PCF8574驱动程序 */

#ifndef __PCF8574_H
#define __PCF8574_H

#include "iic.h"

/* INT中断引脚 */
#define INT_PORT          GPIOB
#define INT_PIN           GPIO_PIN_12
#define INT_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while (0)

/* PCF8574的IO口 */
#define BEEP   0x00    /* 蜂鸣器引脚 */
#define APCINT 0x01    /* 光距中断引脚 */

/* 初始化 */
void pcf8574_init(void);

/* 读写一字节 */
void pcf_write_byte(uint8_t sta);
uint8_t pcf_read_byte();

/* 读写IO口 */
void pcf_write(uint8_t ste, uint8_t dev);
uint8_t pcf_read(uint8_t dev);

/* 变量声明 */
extern GPIO_InitTypeDef int_handler;

#endif
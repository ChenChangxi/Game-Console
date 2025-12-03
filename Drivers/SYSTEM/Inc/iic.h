/* IIC协议 */

#ifndef __IIC_H
#define __IIC_H

#include "delay.h"

/* SCL和SDA引脚 */
#define IIC_PORT          GPIOH
#define IIC_SCL_PIN       GPIO_PIN_4
#define IIC_SDA_PIN       GPIO_PIN_5
#define IIC_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while (0)

/* SCL和SDA和读写 */
#define IIC_SDA_GET(x)    do {x = HAL_GPIO_ReadPin(IIC_PORT, IIC_SDA_PIN);} while (0)
#define IIC_SCL_SET(x,y) \
    do {HAL_GPIO_WritePin(IIC_PORT, IIC_SCL_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);delay_us(y);} while (0)
#define IIC_SDA_SET(x,y) \
    do {HAL_GPIO_WritePin(IIC_PORT, IIC_SDA_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);delay_us(y);} while (0)

/* 初始化 */
void iic_init(void);

/* IIC时序 */
void iic_start(void);               /* 起始信号 */
void iic_send_byte(uint8_t dat);    /* 写一字节 */
uint8_t iic_read_byte(void);        /* 读一字节 */
void iic_wait_ack(void);            /* 等待应答 */
void iic_send_ack(uint8_t sta);     /* 发送应答 */
void iic_end(void);                 /* 停止信号 */

/* 变量声明 */
extern GPIO_InitTypeDef iic_handler;

#endif
/* AT24C02驱动程序 */

#ifndef __AT24C02_H
#define __AT24C02_H

#include "sys.h"
#include "delay.h"

/* SCL和SDA引脚 */
#define ATC_PORT          GPIOH
#define ATC_SCL_PIN       GPIO_PIN_4
#define ATC_SDA_PIN       GPIO_PIN_5
#define ATC_CLK_ENABLE()  do {__HAL_RCC_GPIOH_CLK_ENABLE();} while(0)

/* SCL和SDA和读写 */
#define ATC_SDA_GET(x)    do {x = HAL_GPIO_ReadPin(ATC_PORT, ATC_SDA_PIN);} while(0)
#define ATC_SCL_SET(x,y) \
    do {HAL_GPIO_WritePin(ATC_PORT, ATC_SCL_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);delay_us(y);} while (0)
#define ATC_SDA_SET(x,y) \
    do {HAL_GPIO_WritePin(ATC_PORT, ATC_SDA_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);delay_us(y);} while (0)

/* 初始化 */
void at24c02_init(void);

/* IIC时序 */
void iic_start(void);               /* 起始信号 */
void iic_send_byte(uint8_t dat);    /* 写一字节 */
uint8_t iic_read_byte(void);        /* 读一字节 */
void iic_wait_ack(void);            /* 等待应答 */
void iic_send_ack(uint8_t sta);     /* 发送应答 */
void iic_end(void);                 /* 停止信号 */

/* 读写一字节 */
void atc_write_byte(uint8_t adr, uint8_t dat);
uint8_t atc_read_byte(uint8_t adr);

/* 读写字符串 */
void atc_write(uint8_t addr, uint8_t *buff, uint16_t size);
void atc_read(uint8_t addr, uint8_t *buff, uint16_t size);

/* 变量声明 */
extern uint8_t          atc_ders[];
extern uint8_t          atc_dout[];
extern uint8_t          atc_addr;
extern uint8_t          atc_erse[256];
extern GPIO_InitTypeDef atc_handler;

#endif
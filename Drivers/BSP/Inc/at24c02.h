/* AT24C02驱动程序 */

#ifndef __AT24C02_H
#define __AT24C02_H

#include "iic.h"

/* 初始化 */
void at24c02_init(void);

/* 读写一字节 */
void atc_write_byte(uint8_t adr, uint8_t dat);
uint8_t atc_read_byte(uint8_t adr);

/* 读写字符串 */
void atc_write(uint8_t addr, uint8_t *buff, uint16_t size);
void atc_read(uint8_t addr, uint8_t *buff, uint16_t size);

/* 变量声明 */
extern uint8_t atc_ders[];
extern uint8_t atc_dout[];
extern uint8_t atc_addr;
extern uint8_t atc_erse[256];

#endif
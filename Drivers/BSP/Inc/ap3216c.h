/* AP3216C驱动程序 */

#ifndef __AP3216C_H
#define __AP3216C_H

#include "iic.h"

/* 初始化 */
void ap3216c_init(void);

/* 读写一字节 */
void apc_write_byte(uint8_t adr, uint8_t dat);
uint8_t apc_read_byte(uint8_t adr);

#endif
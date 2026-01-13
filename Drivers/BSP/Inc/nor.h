/* W25Q256驱动 */

#ifndef __W25Q256_H
#define __W25Q256_H

#include "qspi.h"

/* NOR FLASH参数 */
#define PAGE   256
#define SECTOR PAGE * 16

/* 初始化NOR FLASH */
void nor_init(void);

/* 读NOR FLASH */
void nor_read(uint32_t adr, uint8_t *dat, uint32_t num);

/* 写NOR FLASH */
void nor_write(uint32_t adr, uint8_t *dat, uint32_t num);

/* 页写NOR FLASH */
void nor_page_write(uint32_t adr, uint8_t *dat, uint32_t num);

/* 擦除NOR FLASH */
void nor_erase();

#endif
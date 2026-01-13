/* W25Q256驱动 */

#ifndef __W25Q256_H
#define __W25Q256_H

#include "qspi.h"

/* NOR FLASH参数 */
#define PAGE   256
#define SECTOR PAGE * 16

/* NOR FLASH指令 */
#define WriteEnable           0x06         /* 写使能 */
#define WriteDisable          0x04         /* 写失能 */
#define ReadStatusReg1        0x05         /* 读REG1 */
#define ReadStatusReg2        0x35         /* 读REG2 */
#define ReadStatusReg3        0x15         /* 读REG3 */
#define PageProgramQuad       0x32         /* 页写 */
#define FastReadQuad          0xeb         /* 快读 */
#define BlockErase            0xd8         /* 块擦除 */
#define SectorErase           0x20         /* 区擦除 */
#define ChipErase             0xc7         /* 片擦除 */
#define Enable4ByteAddr       0xb7         /* 进入4字节模式 */
#define ExitQPIMode           0xff         /* 退出QPI模式 */

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
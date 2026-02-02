/* QSPI驱动 */

#ifndef __QSPI_H
#define __QSPI_H

#include "sys.h"

/* QSPI */
#define QSPI_IOx_PORT               GPIOF
#define QSPI_CLK_NCS_PORT           GPIOB
#define QSPI_IO32_PIN               GPIO_PIN_6 | GPIO_PIN_7
#define QSPI_IO01_PIN               GPIO_PIN_8 | GPIO_PIN_9
#define QSPI_CLK_PIN                GPIO_PIN_2
#define QSPI_NCS_PIN                GPIO_PIN_6
#define QSPI_AF_X                   GPIO_AF9_QUADSPI
#define QSPI_AF_Y                   GPIO_AF10_QUADSPI
#define QSPI_MDMA_CHANNEL           MDMA_Channel0
#define QSPI_CLK_ENABLE()           do {__HAL_RCC_QSPI_CLK_ENABLE();}  while (0)
#define QSPI_MDMA_ENABLE()          do {__HAL_RCC_MDMA_CLK_ENABLE();}  while (0)
#define QSPI_IOx_CLK_ENABLE()       do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)
#define QSPI_CLK_NCS_CLK_ENABLE()   do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define QSPI_TIM_OUT                (1000)
#define QSPI_MDMA_BLOCK             (8 * 1024)

/* 内存映射地址 */
#define QSPI_BASE (uint32_t)(0x90000000)

/* 枚举定义 */
typedef enum {INDIRECT, MEMORYMAP} QSPI_Mode;

/* 初始化QSPI */
void qspi_init(void);

/* QSPI接口 */
void spi_cmd(uint8_t cmd);                                                   /* 发送指令 */
void spi_read(uint8_t cmd, uint8_t *sta, uint8_t num);                       /* 发送指令读数据 */
void spi_write(uint8_t cmd, uint8_t *sta, uint8_t num);                      /* 发送指令写数据 */
void spi_erase(uint8_t cmd, uint32_t adr);                                   /* 发送指令地址（擦除）*/
void spi_write_data(uint8_t cmd, uint32_t adr, uint8_t *dat, uint32_t num);  /* 发送指令地址写数据 */
void spi_indirect(void);                                                     /* 进入间接模式 */
void spi_memory_map(uint8_t cmd);                                            /* 进入内存映射模式 */

/* 变量声明 */
extern QSPI_Mode                qspi_mode;
extern MDMA_HandleTypeDef       qspi_mdma_handler;
extern QSPI_HandleTypeDef       qspi_init_handler;
extern QSPI_CommandTypeDef      qspi_comd_handler;
extern QSPI_MemoryMappedTypeDef qspi_mema_handler;

#endif
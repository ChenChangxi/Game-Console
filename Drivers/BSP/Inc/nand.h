/* MT29F4G08驱动 */

#ifndef __MT29F4G08_H
#define __MT29F4G08_H

#include "delay.h"

/* 引脚和时钟 */
#define NAND_NWE_PORT          GPIOD           /* 读 */
#define NAND_NOE_PORT          GPIOD           /* 写 */
#define NAND_NCE_PORT          GPIOG           /* 片选 */
#define NAND_NWA_PORT          GPIOD           /* 等待 */

#define NAND_NWE_PIN           GPIO_PIN_5
#define NAND_NOE_PIN           GPIO_PIN_4
#define NAND_NCE_PIN           GPIO_PIN_9
#define NAND_NWA_PIN           GPIO_PIN_6

#define NAND_AF                GPIO_AF12_FMC

#define NAND_NWE_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define NAND_NOE_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define NAND_NCE_CLK_ENABLE()  do {__HAL_RCC_GPIOG_CLK_ENABLE();} while (0)
#define NAND_NWA_CLK_ENABLE()  do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)

/* NAND状态 */
#define NAND_BUSY(x) \
    do {HAL_GPIO_WritePin(NAND_NWA_PORT, NAND_NWA_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* NAND时序 */
#define TADL  70   /* 址建立(ns) */
#define TWHR  60   /* 写转读(ns) */
#define TRHW  100  /* 读转写(ns) */
#define TPROG 200  /* 页编程(us) */
#define TBERS 700  /* 块擦除(us) */

/* NAND参数 */
#define NAND_ECC_SEC     (512)
#define NAND_ECC_SIZE    (64)
#define NAND_PAGE_NUM    (64)
#define NAND_PAGE_SIZE   (2048)
#define NAND_BLOCK_NUM   (4096)
#define NAND_BLOCK_PAGE  (NAND_PAGE_NUM * NAND_BLOCK_NUM)

/* NAND控制 */
#define DAT       *(volatile uint8_t *)(NAND_BASE)
#define CMD       *(volatile uint8_t *)(NAND_BASE | (uint32_t)(1<<16))
#define ADR       *(volatile uint8_t *)(NAND_BASE | (uint32_t)(1<<17))
#define NAND_BASE  (uint32_t)(0X80000000)

/* NAND指令 */
#define Reset              0XFF           /* 复位 */
#define Feature            0XEF           /* 特性 */
#define Read               0X00           /* 始读 */
#define ReadPage           0X30           /* 页读 */
#define Write              0X80           /* 始写 */
#define WritePage          0X10           /* 页写 */
#define Erase              0X60           /* 始擦除 */
#define EraseBlock         0XD0           /* 块擦除 */
#define MoveSource         0X00           /* 源地址（始移）*/
#define MoveSourcePage     0X35           /* 源地址（页移）*/
#define MoveDestinate      0X85           /* 目标地址（始移）*/
#define MoveDestinatePage  0X10           /* 目标地址（页移）*/

/* 初始化MT29F4G08 */
void nand_init(void);

/* 页读NAND FLASH */
void nand_page_read(uint32_t num, uint16_t adr, uint8_t *dat, uint32_t con);

/* 页写NAND FLASH */
void nand_page_write(uint32_t num, uint16_t adr, uint8_t *dat, uint32_t con);

/* 块擦NAND FLASH */
void nand_block_erase(uint32_t num);

/* 变量声明 */
extern NAND_HandleTypeDef         nand_init_handler;
extern FMC_NAND_PCC_TimingTypeDef nand_time_handler;

#endif
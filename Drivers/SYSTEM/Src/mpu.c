#include "mpu.h"

MPU_Region_InitTypeDef mpu_set_handler;

void mpu_set(uint8_t num, uint32_t bas, uint8_t siz, uint8_t exe,
             uint8_t acc, uint8_t  tex, uint8_t cae, uint8_t buf, uint8_t sha) {

    HAL_MPU_Disable();

    mpu_set_handler.Enable           = MPU_REGION_ENABLE;  /* 使能内存区 */
    mpu_set_handler.Number           = num;                /* 区域号 */
    mpu_set_handler.BaseAddress      = bas;                /* 区域基地址 */
    mpu_set_handler.Size             = siz;                /* 区域大小 */
    mpu_set_handler.SubRegionDisable = 0x00;               /* 开启子区域 */
    mpu_set_handler.DisableExec      = exe;                /* 是否取指 */
    mpu_set_handler.AccessPermission = acc;                /* 访问权限 */
    mpu_set_handler.TypeExtField     = tex;                /* Cache策略 */
    mpu_set_handler.IsCacheable      = cae;                /* 是否Cache */
    mpu_set_handler.IsBufferable     = buf;                /* 是否Buffer */
    mpu_set_handler.IsShareable      = sha;                /* 是否共享 */
    HAL_MPU_ConfigRegion(&mpu_set_handler);

    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);                /* 使能对未配置地址访问，进入中断关闭MPU */
}

void memory_protect(void) {

    mpu_set(MPU_REGION_NUMBER2,
            0x24000000,                      /* AXI SRAM */
            MPU_REGION_SIZE_512KB,           /* D1域 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL1,                  /* TEX低位为1 */
            MPU_ACCESS_CACHEABLE,            /* 允许Cache */
            MPU_ACCESS_BUFFERABLE,           /* 允许Buffer（同步）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */

    mpu_set(MPU_REGION_NUMBER3,
            0x30000000,                      /* SRAM1,SRAM2,SRAM3 */
            MPU_REGION_SIZE_512KB,           /* D2域 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL1,                  /* TEX低位为1 */
            MPU_ACCESS_CACHEABLE,            /* 允许Cache */
            MPU_ACCESS_BUFFERABLE,           /* 允许Buffer（同步）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */

    mpu_set(MPU_REGION_NUMBER4,
            0x38000000,                      /* SRAM4 */
            MPU_REGION_SIZE_64KB,            /* D3域 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL1,                  /* TEX低位为1 */
            MPU_ACCESS_CACHEABLE,            /* 允许Cache */
            MPU_ACCESS_BUFFERABLE,           /* 允许Buffer（同步）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */

    mpu_set(MPU_REGION_NUMBER5,
            0x60000000,                      /* LCD */
            MPU_REGION_SIZE_1MB,             /* FMC BANK1 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL0,                  /* TEX低位为0 */
            MPU_ACCESS_NOT_CACHEABLE,        /* 禁止Cache */
            MPU_ACCESS_NOT_BUFFERABLE,       /* 禁止Buffer（异步，有时序要求）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */
    
    mpu_set(MPU_REGION_NUMBER6,
            0x80000000,                      /* NAND FLASH */
            MPU_REGION_SIZE_256KB,           /* FMC BANK3 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL0,                  /* TEX低位为0 */
            MPU_ACCESS_NOT_CACHEABLE,        /* 禁止Cache */
            MPU_ACCESS_NOT_BUFFERABLE,       /* 禁止Buffer（异步，有时序要求）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */

    mpu_set(MPU_REGION_NUMBER7,
            0xC0000000,                      /* SDRAM */
            MPU_REGION_SIZE_32MB,            /* FMC SDRAM BANK1 */
            MPU_INSTRUCTION_ACCESS_ENABLE,   /* 允许取指 */
            MPU_REGION_FULL_ACCESS,          /* 完全读写 */
            MPU_TEX_LEVEL1,                  /* TEX低位为1 */
            MPU_ACCESS_CACHEABLE,            /* 允许Cache */
            MPU_ACCESS_BUFFERABLE,           /* 允许Buffer（同步）*/
            MPU_ACCESS_NOT_SHAREABLE);       /* 不允许共享 */
}
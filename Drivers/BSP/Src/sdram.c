#include "sdram.h"

SDRAM_HandleTypeDef      sdram_init_handler;
FMC_SDRAM_TimingTypeDef  sdram_time_handler;
FMC_SDRAM_CommandTypeDef sdram_comd_handler;

void sdram_init(void) {

    sdram_init_handler.Instance = FMC_SDRAM_DEVICE;
    sdram_init_handler.Init.SDBank             = FMC_SDRAM_BANK1;                     /* SDRAM BANK1 */
    sdram_init_handler.Init.InternalBankNumber = ;             
    sdram_init_handler.Init.SDClockPeriod      = ;       /* 分频系数 */
    sdram_init_handler.Init.CASLatency         = ;
    sdram_init_handler.Init.ReadBurst          = ;
    sdram_init_handler.Init.ReadPipeDelay      = ;
    sdram_init_handler.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;  /* 写使能 */
    sdram_init_handler.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_16;          /* 数据宽度 */
    sdram_init_handler.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_13;           /* 行地址宽度 */
    sdram_init_handler.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;         /* 列地址宽度 */
    sdram_time_handler.RCDDelay             = ;
    sdram_time_handler.RPDelay              = ;
    sdram_time_handler.WriteRecoveryTime    = ;
    sdram_time_handler.RowCycleDelay        = ;
    sdram_time_handler.LoadToActiveDelay    = ;
    sdram_time_handler.SelfRefreshTime      = ;
    sdram_time_handler.ExitSelfRefreshDelay = ;
    HAL_SDRAM_Init(&sdram_init_handler, &sdram_time_handler);

    w9825g6kh6_init();

    HAL_SDRAM_ProgramRefreshRate(&sdram_init_handler, 1);
}

void w9825g6kh6_init(void) {

    HAL_SDRAM_SendCommand(&sdram_init_handler, &sdram_comd_handler, 1);
}
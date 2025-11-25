#include "sdram.h"

SDRAM_HandleTypeDef      sdram_init_handler;
FMC_SDRAM_TimingTypeDef  sdram_time_handler;
FMC_SDRAM_CommandTypeDef sdram_comd_handler;

void sdram_init(void) {

    sdram_init_handler.Instance                = FMC_SDRAM_DEVICE;
    sdram_init_handler.Init.SDBank             = FMC_SDRAM_BANK1;                    /* SDRAM BANK1 */
    sdram_init_handler.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;       /* 内部BANK数 */
    sdram_init_handler.Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2;           /* 分频系数 */
    sdram_init_handler.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;            /* 读延后SDCLK */
    sdram_init_handler.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;            /* 读突发使能 */
    sdram_init_handler.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;            /* 读延后HCLK（RGB稳定）*/
    sdram_init_handler.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE; /* 写使能 */
    sdram_init_handler.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_16;         /* 数据宽度 */
    sdram_init_handler.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_13;          /* 行地址宽度 */
    sdram_init_handler.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;        /* 列地址宽度 */

    sdram_time_handler.RCDDelay             = 2;  /* TRCD 激活到读写时间 */
    sdram_time_handler.RPDelay              = 2;  /* TRP  预充电时间 */
    sdram_time_handler.WriteRecoveryTime    = 2;  /* TWR  写数据时间 */
    sdram_time_handler.RowCycleDelay        = 8;  /* TRC  行周期时间 */
    sdram_time_handler.LoadToActiveDelay    = 2;  /* TMRD 设置模式到激活时间 */
    sdram_time_handler.SelfRefreshTime      = 9;  /* TRFC 行刷新时间 */
    sdram_time_handler.ExitSelfRefreshDelay = 9;  /* TXSR 休眠结束到激活时间 */

    HAL_SDRAM_Init(&sdram_init_handler, &sdram_time_handler);w9825g6kh6_init();
    HAL_SDRAM_ProgramRefreshRate(&sdram_init_handler, 938 - 20);   /* 行刷新速度（留裕量提前刷新）*/
    memset((void *)0xC0000000, 0, 32 * 1024 * 1024);               /* 重置或上电后清理SDRAM */
    sys_cache_sram_sync(0xC0000000, (uint32_t)(32 * 1024 * 1024)); /* 将DCache刷回SDRAM */
}

void w9825g6kh6_init(void) {

    sdram_comd_handler.CommandMode   = FMC_SDRAM_CMD_CLK_ENABLE;
    sdram_comd_handler.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    HAL_SDRAM_SendCommand(&sdram_init_handler, &sdram_comd_handler, 0x1000);     /* 使能时钟 */

    delay_us(500);

    sdram_comd_handler.CommandMode   = FMC_SDRAM_CMD_PALL;
    HAL_SDRAM_SendCommand(&sdram_init_handler, &sdram_comd_handler, 0x1000);     /* 预充电所有单元 */

    sdram_comd_handler.CommandMode       = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    sdram_comd_handler.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&sdram_init_handler, &sdram_comd_handler, 0x1000);     /* 连续自动刷新 */

    sdram_comd_handler.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    sdram_comd_handler.ModeRegisterDefinition = (uint32_t) SDRAM_MODEREG_BURST_LENGTH_1        |   /* 突发长度 */
                                                           SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |   /* 突发类型 */
                                                           SDRAM_MODEREG_CAS_LATENCY_3         |   /* 读延后SDCLK */
                                                           SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;   /* 写突发失能 */
    HAL_SDRAM_SendCommand(&sdram_init_handler, &sdram_comd_handler, 0x1000);     /* 设置模式寄存器 */
}
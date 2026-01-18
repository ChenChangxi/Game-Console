#include "qspi.h"

QSPI_Mode                qspi_mode;
MDMA_HandleTypeDef       qspi_mdma_handler;
QSPI_HandleTypeDef       qspi_init_handler;
QSPI_CommandTypeDef      qspi_comd_handler;
QSPI_MemoryMappedTypeDef qspi_mema_handler;

void qspi_init(void) {

    qspi_init_handler.Instance                = QUADSPI;

    qspi_init_handler.Init.FlashID            = QSPI_FLASH_ID_1;                 /* Flash */
    qspi_init_handler.Init.DualFlash          = QSPI_DUALFLASH_DISABLE;          /* 双闪存模式 */
    qspi_init_handler.Init.FifoThreshold      = 4;                               /* FIFO阈值 */
    qspi_init_handler.Init.ClockPrescaler     = 2 - 1;                           /* PLL2R */
    qspi_init_handler.Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_HALFCYCLE;  /* 采样移位 */

    qspi_init_handler.Init.ClockMode          = QSPI_CLOCK_MODE_0;               /* SPI模式 */
    qspi_init_handler.Init.FlashSize          = 25 - 1;                          /* Flash大小（地址位数）*/
    qspi_init_handler.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;       /* 片选高电平时间 */

    qspi_comd_handler.DdrMode                 = QSPI_DDR_MODE_DISABLE;           /* 双倍速率模式 */
    qspi_comd_handler.SIOOMode                = QSPI_SIOO_INST_EVERY_CMD;        /* 每个事务发送指令 */
    qspi_comd_handler.DdrHoldHalfCycle        = QSPI_DDR_HHC_ANALOG_DELAY;       /* DDR最后延时半周期 */
    qspi_comd_handler.InstructionMode         = QSPI_INSTRUCTION_1_LINE;         /* 指令模式 */
    qspi_comd_handler.AddressSize             = QSPI_ADDRESS_32_BITS;            /* 地址长度 */
    qspi_comd_handler.AlternateBytes          = 0;                               /* 交替字节 */
    qspi_comd_handler.AlternateBytesSize      = QSPI_ALTERNATE_BYTES_8_BITS;     /* 交替字节长度 */

    HAL_QSPI_Init(&qspi_init_handler);
}

void spi_cmd(uint8_t cmd) {

    qspi_comd_handler.Instruction = cmd;
    qspi_comd_handler.AddressMode = QSPI_ADDRESS_NONE;
    qspi_comd_handler.DataMode    = QSPI_DATA_NONE;
    HAL_QSPI_Command(&qspi_init_handler, &qspi_comd_handler, QSPI_TIM_OUT);
}

void spi_read(uint8_t cmd, uint8_t *sta, uint8_t num) {

    qspi_comd_handler.Instruction = cmd;
    qspi_comd_handler.AddressMode = QSPI_ADDRESS_NONE;
    qspi_comd_handler.NbData      = num;                  /* 数据长度 */
    qspi_comd_handler.DataMode    = QSPI_DATA_1_LINE;     /* 数据模式 */
    HAL_QSPI_Command(&qspi_init_handler, &qspi_comd_handler, QSPI_TIM_OUT);
    HAL_QSPI_Receive(&qspi_init_handler, sta, QSPI_TIM_OUT);
}

void spi_write(uint8_t cmd, uint8_t *sta, uint8_t num) {

    qspi_comd_handler.Instruction = cmd;
    qspi_comd_handler.AddressMode = QSPI_ADDRESS_NONE;
    qspi_comd_handler.NbData      = num;                  /* 数据长度 */
    qspi_comd_handler.DataMode    = QSPI_DATA_1_LINE;     /* 数据模式 */
    HAL_QSPI_Command(&qspi_init_handler, &qspi_comd_handler, QSPI_TIM_OUT);
    HAL_QSPI_Transmit(&qspi_init_handler, sta, QSPI_TIM_OUT);
}

void spi_erase(uint8_t cmd, uint32_t adr) {

    qspi_comd_handler.Instruction = cmd;
    qspi_comd_handler.DataMode    = QSPI_DATA_NONE;
    qspi_comd_handler.Address     = adr;                  /* 地址 */
    qspi_comd_handler.AddressMode = QSPI_ADDRESS_1_LINE;  /* 地址模式 */
    HAL_QSPI_Command(&qspi_init_handler, &qspi_comd_handler, QSPI_TIM_OUT);
}

void spi_write_data(uint8_t cmd, uint32_t adr, uint8_t *dat, uint32_t num) {

    qspi_comd_handler.Instruction = cmd;
    qspi_comd_handler.Address     = adr;                  /* 地址 */
    qspi_comd_handler.AddressMode = QSPI_ADDRESS_1_LINE;  /* 地址模式 */
    qspi_comd_handler.NbData      = num;                  /* 数据长度 */
    qspi_comd_handler.DataMode    = QSPI_DATA_4_LINES;    /* 数据模式 */
    HAL_QSPI_Command(&qspi_init_handler, &qspi_comd_handler, QSPI_TIM_OUT);
    HAL_QSPI_Transmit_DMA(&qspi_init_handler, dat);
}

void spi_indirect(void) {

    qspi_mode                                   = INDIRECT;
    qspi_comd_handler.DummyCycles               = 0;
    qspi_comd_handler.AlternateByteMode         = QSPI_ALTERNATE_BYTES_NONE;

    qspi_mdma_handler.Init.Request              = MDMA_REQUEST_QUADSPI_FIFO_TH;
    qspi_mdma_handler.Init.DestinationInc       = MDMA_DEST_INC_DISABLE;
    qspi_mdma_handler.Init.DestBurst            = MDMA_SOURCE_BURST_SINGLE;
    qspi_mdma_handler.Init.TransferTriggerMode  = MDMA_BUFFER_TRANSFER;
    qspi_mdma_handler.Init.BufferTransferLength = 32;

    HAL_MDMA_Init(&qspi_mdma_handler);
    HAL_QSPI_Abort(&qspi_init_handler);
}

void spi_memory_map(uint8_t cmd) {

    qspi_mode                                   = MEMORYMAP;
    qspi_comd_handler.Instruction               = cmd;
    qspi_comd_handler.AddressMode               = QSPI_ADDRESS_4_LINES;          /* 地址模式 */  
    qspi_comd_handler.DataMode                  = QSPI_DATA_4_LINES;             /* 数据模式 */
    qspi_comd_handler.DummyCycles               = 4;                             /* 空指令周期 */
    qspi_comd_handler.AlternateByteMode         = QSPI_ALTERNATE_BYTES_4_LINES;  /* 交替字节模式 */

    qspi_mema_handler.TimeOutPeriod             = 
    qspi_mema_handler.TimeOutActivation         = 

    qspi_mdma_handler.Init.Request              = MDMA_REQUEST_SW;
    qspi_mdma_handler.Init.DestinationInc       = MDMA_DEST_INC_BYTE;
    qspi_mdma_handler.Init.DestBurst            = MDMA_DEST_BURST_4BEATS;
    qspi_mdma_handler.Init.TransferTriggerMode  = MDMA_REPEAT_BLOCK_TRANSFER;
    qspi_mdma_handler.Init.BufferTransferLength = 128;

    HAL_MDMA_Init(&qspi_mdma_handler);
    HAL_QSPI_MemoryMapped(&qspi_init_handler, &qspi_comd_handler, &qspi_mema_handler);
}
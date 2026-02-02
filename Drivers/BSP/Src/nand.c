#include "nand.h"

NAND_HandleTypeDef         nand_init_handler;
FMC_NAND_PCC_TimingTypeDef nand_time_handler;

void nand_init(void) {

    nand_init_handler.Instance             = FMC_NAND_DEVICE;
    nand_init_handler.Init.NandBank        = FMC_NAND_BANK3;                  /* NAND BANK3 */
    nand_init_handler.Init.MemoryDataWidth = FMC_NAND_MEM_BUS_WIDTH_8;        /* 总线宽度 */
    nand_init_handler.Init.EccComputation  = FMC_NAND_ECC_DISABLE;            /* ECC关闭 */
    nand_init_handler.Init.ECCPageSize     = FMC_NAND_ECC_PAGE_SIZE_512BYTE;  /* ECC计算单位 */
    nand_init_handler.Init.TARSetupTime    =                                  /* 地址建立时间 */
    nand_init_handler.Init.TCLRSetupTime   =                                  /* 命令建立时间 */

    nand_time_handler.SetupTime     = 
    nand_time_handler.HoldSetupTime = 
    nand_time_handler.WaitSetupTime = 
    nand_time_handler.HiZSetupTime  = 

    HAL_NAND_Init(&nand_init_handler, &nand_time_handler, &nand_time_handler);
}

void nand_page_read(uint32_t num, uint16_t adr, uint8_t *dat, uint32_t con) {

    CMD = Read;
    ADR = (uint8_t)adr;ADR = (uint8_t)(adr>>8);
    ADR = (uint8_t)num;ADR = (uint8_t)(num>>8);ADR = (uint8_t)(num>>16);
    CMD = ReadPage;
}

void nand_page_write(uint32_t num, uint16_t adr, uint8_t *dat, uint32_t con) {

    CMD = Write;
    ADR = (uint8_t)adr;ADR = (uint8_t)(adr>>8);
    ADR = (uint8_t)num;ADR = (uint8_t)(num>>8);ADR = (uint8_t)(num>>16);
    CMD = WritePage;
}

void nand_block_erase(uint32_t num) {

    num *= NAND_PAGE_NUM;CMD = Erase;
    ADR = (uint8_t)num;ADR = (uint8_t)(num>>8);ADR = (uint8_t)(num>>16);
    CMD = EraseBlock;delay_us(TBERS);
}
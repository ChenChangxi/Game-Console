#include "nand.h"

NAND_HandleTypeDef         nand_init_handler;
FMC_NAND_PCC_TimingTypeDef nand_time_handler;

void nand_init(void) {

    nand_init_handler.Instance             = FMC_NAND_DEVICE;
    nand_init_handler.Init.NandBank        = FMC_NAND_BANK3;            /* NAND BANK3 */
    nand_init_handler.Init.MemoryDataWidth = FMC_NAND_MEM_BUS_WIDTH_8;  /* 命令/地址/数据宽度 */
    nand_init_handler.Init.EccComputation  = FMC_NAND_ECC_DISABLE;      /* 需要计算ECC时打开 */
    nand_init_handler.Init.ECCPageSize     = 
    nand_init_handler.Init.TARSetupTime    = 
    nand_init_handler.Init.TCLRSetupTime   = 
    nand_init_handler.Init.TCLRSetupTime   = 

    nand_time_handler.SetupTime     = 
    nand_time_handler.HoldSetupTime = 
    nand_time_handler.WaitSetupTime = 
    nand_time_handler.HiZSetupTime  = 

    HAL_NAND_Init(&nand_init_handler, &nand_time_handler, &nand_time_handler);
}
#include "nor.h"

void nor_init(void) {

    uint8_t reg;
    spi_cmd(ExitQPIMode);                                      /* 退出QPI模式 */
    spi_cmd(WriteEnable);spi_cmd(Enable4ByteAddr);             /* 进入四字节模式 */
    spi_read(ReadStatusReg2, &reg, 1);reg |= 1<<1;             /* 读STATUSREG2 */
    spi_cmd(WriteEnable);spi_write(WriteStatusReg2, &reg, 1);  /* 进入QSPI模式 */
}

void nor_read(uint32_t adr, uint8_t *dat, uint32_t num) {

    uint32_t cou = num / QSPI_MDMA_BLOCK, res = num % QSPI_MDMA_BLOCK, inc = cou * QSPI_MDMA_BLOCK;
    HAL_MDMA_Start(&qspi_mdma_handler, adr, (uint32_t)dat, QSPI_MDMA_BLOCK, cou);
    HAL_MDMA_Start(&qspi_mdma_handler, adr + inc, (uint32_t)(dat + inc), res, 1);
}

void nor_page_write(uint32_t adr, uint8_t *dat, uint32_t num) {

    uint16_t res = PAGE - adr % PAGE;
    if (num < res) res = num;
    while (true) {

        spi_cmd(WriteEnable);spi_write_data(PageProgramQuad, adr, dat, res);wait_busy();
        if (num == res) break;
        else {

            adr += res, dat += res, num -= res;
            if (num > PAGE) res = PAGE;else res = num;
        }
    }
}

void nor_erase(uint32_t adr) {spi_cmd(WriteEnable);spi_erase(SectorErase, adr);wait_busy();}

void wait_busy(void) {uint8_t reg;spi_read(ReadStatusReg1, reg, 1);while (reg & 0x01);}
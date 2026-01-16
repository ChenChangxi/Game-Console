#include "nor.h"

void nor_init(void) {

    uint8_t reg;
    spi_cmd(ExitQPIMode);                                      /* 退出QPI模式 */
    spi_cmd(WriteEnable);spi_cmd(Enable4ByteAddr);             /* 进入四字节模式 */
    spi_read(ReadStatusReg2, &reg, 1);reg |= 1<<1;             /* 读STATUSREG2 */
    spi_cmd(WriteEnable);spi_write(WriteStatusReg2, &reg, 1);  /* 进入QSPI模式 */
}

void nor_write(uint32_t adr, uint8_t *dat, uint32_t num) {

    uint8_t tem[SECTOR], era = 0;
    uint16_t seo = adr % SECTOR, res = SECTOR - seo;
    uint32_t sec = adr / SECTOR;
    if (num < res) res = num;
    while (true) {

        nor_read(sec * SECTOR, tem, SECTOR);
        for (uint16_t i=0;i<res;++i) if (tem[i] != 0xff) {nor_erase(adr);era = 1;break;}
        memcpy(tem + seo, (const void *)adr, res);
        if (era) nor_page_write(sec * SECTOR, tem, SECTOR);else nor_page_write(adr, dat, res);
        if (num == res) break;
        else {

            adr += res, dat += res, num -= res, sec += 1, seo = 0, era = 0;
            if (num > SECTOR) res = SECTOR;else res = num;
        }
    }
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
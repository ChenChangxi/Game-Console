#include "at24c02.h"

uint8_t atc_ders[] = "已擦除\r\n";
uint8_t atc_dout[] = "数据溢出\r\n";
uint8_t atc_addr;
uint8_t atc_erse[256] = {0xff};

void at24c02_init(void) {atc_read(0xff, &atc_addr, 1);}

void atc_write_byte(uint8_t adr, uint8_t dat) {

    iic_start();
    iic_send_byte(0xA0);iic_wait_ack();iic_send_byte(adr);iic_wait_ack();iic_send_byte(dat);iic_wait_ack();
    iic_end();delay_ms(10);
}

uint8_t atc_read_byte(uint8_t adr) {

    uint8_t dat = 0;iic_start();
    iic_send_byte(0xA0);iic_wait_ack();iic_send_byte(adr);iic_wait_ack();iic_start();iic_send_byte(0xA1);
    iic_wait_ack();dat = iic_read_byte();iic_send_ack(1);iic_end();return dat;
}

void atc_write(uint8_t addr, uint8_t *buff, uint16_t size) {while (size--) atc_write_byte(addr++, *buff++);}

void atc_read(uint8_t addr, uint8_t *buff, uint16_t size) {while (size--) *buff++ = atc_read_byte(addr++);}
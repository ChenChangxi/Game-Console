#include "at24c02.h"

uint8_t          atc_ders[] = "已擦除\r\n";
uint8_t          atc_dout[] = "数据溢出\r\n";
uint8_t          atc_addr;
uint8_t          atc_erse[256] = {0xff};
GPIO_InitTypeDef atc_handler;

void at24c02_init(void) {

    ATC_CLK_ENABLE();

    atc_handler.Pin   = ATC_SCL_PIN;
    atc_handler.Mode  = GPIO_MODE_OUTPUT_PP;
    atc_handler.Pull  = GPIO_PULLUP;
    atc_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATC_PORT, &atc_handler);

    atc_handler.Pin   = ATC_SDA_PIN;
    atc_handler.Mode  = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(ATC_PORT, &atc_handler);

    atc_read(0xff, &atc_addr, 1);
}

void iic_start(void) {ATC_SDA_SET(1,0);ATC_SCL_SET(1,2);ATC_SDA_SET(0,2);ATC_SCL_SET(0,2);}

void iic_send_byte(uint8_t dat) {

    for (uint8_t i=0;i<8;++i) {ATC_SDA_SET((dat & 0x80)>>7,2);ATC_SCL_SET(1,2);ATC_SCL_SET(0,2);dat <<= 1;}
}

uint8_t iic_read_byte(void) {

    uint8_t dat = 0,sta = 0;ATC_SDA_SET(1,2);
    for (uint8_t i=0;i<8;++i) {dat <<= 1;ATC_SCL_SET(1,2);ATC_SDA_GET(sta);ATC_SCL_SET(0,2);dat += sta;} 
    return dat;
}

void iic_wait_ack(void) {
    
    uint8_t sta = 0;ATC_SDA_SET(1,2);ATC_SCL_SET(1,2);ATC_SDA_GET(sta);ATC_SCL_SET(0,2);if (sta) iic_end();
}

void iic_send_ack(uint8_t sta) {ATC_SDA_SET(sta,2);ATC_SCL_SET(1,2);ATC_SCL_SET(0,2);}

void iic_end(void) {ATC_SDA_SET(0,0);ATC_SCL_SET(1,2);ATC_SDA_SET(1,2);}

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
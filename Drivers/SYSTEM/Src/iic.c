#include "iic.h"

GPIO_InitTypeDef iic_handler;

void iic_init(void) {

    IIC_CLK_ENABLE();

    iic_handler.Pin   = IIC_SCL_PIN;
    iic_handler.Mode  = GPIO_MODE_OUTPUT_PP;
    iic_handler.Pull  = GPIO_PULLUP;
    iic_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(IIC_PORT, &iic_handler);

    iic_handler.Pin   = IIC_SDA_PIN;
    iic_handler.Mode  = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(IIC_PORT, &iic_handler);
}

void iic_start(void) {IIC_SDA_SET(1,0);IIC_SCL_SET(1,2);IIC_SDA_SET(0,2);IIC_SCL_SET(0,2);}

void iic_send_byte(uint8_t dat) {

    for (uint8_t i=0;i<8;++i) {IIC_SDA_SET((dat & 0x80)>>7,2);IIC_SCL_SET(1,2);IIC_SCL_SET(0,2);dat <<= 1;}
}

uint8_t iic_read_byte(void) {

    uint8_t dat = 0,sta = 0;IIC_SDA_SET(1,2);
    for (uint8_t i=0;i<8;++i) {dat <<= 1;IIC_SCL_SET(1,2);IIC_SDA_GET(sta);IIC_SCL_SET(0,2);dat += sta;} 
    return dat;
}

void iic_wait_ack(void) {
    
    uint8_t sta = 0;IIC_SDA_SET(1,2);IIC_SCL_SET(1,2);IIC_SDA_GET(sta);IIC_SCL_SET(0,2);if (sta) iic_end();
}

void iic_send_ack(uint8_t sta) {IIC_SDA_SET(sta,2);IIC_SCL_SET(1,2);IIC_SCL_SET(0,2);}

void iic_end(void) {IIC_SDA_SET(0,0);IIC_SCL_SET(1,2);IIC_SDA_SET(1,2);}
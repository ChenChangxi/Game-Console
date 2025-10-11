#include "pcf8574.h"

GPIO_InitTypeDef int_handler;

void pcf8574_init(void) {

    INT_CLK_ENABLE();

    int_handler.Pin   = INT_PIN;
    int_handler.Mode  = GPIO_MODE_IT_FALLING;
    int_handler.Pull  = GPIO_PULLUP;
    int_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(INT_PORT, &int_handler);

    pcf_write_byte(0xff);     /* 输入正常（准双向弱上拉，强下拉）*/
}

void pcf_write_byte(uint8_t sta) {

    iic_start();iic_send_byte(0x40);iic_wait_ack();iic_send_byte(sta);iic_wait_ack();iic_end();delay_ms(10);
}

uint8_t pcf_read_byte() {

    uint8_t sta = 0;
    iic_start();iic_send_byte(0x41);iic_wait_ack();sta = iic_read_byte();iic_send_ack(1);iic_end();
    return sta;
}

void pcf_write(uint8_t ste, uint8_t dev) {
    
    uint8_t sta = pcf_read_byte();if (ste) pcf_write_byte(sta | (1<<dev));else pcf_write_byte(sta & ~(1<<dev));
}

uint8_t pcf_read(uint8_t dev) {uint8_t sta = pcf_read_byte();return sta & (1<<dev);}
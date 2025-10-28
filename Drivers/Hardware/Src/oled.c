#include "oled.h"

static uint8_t   oled_ram[128][8];
GPIO_InitTypeDef oled_handler;

void oled_init(void) {

    OLED_CON_CLK_ENABLE();
    OLED_INS_CLK_ENABLE();

    oled_handler.Pin   = OLED_CON_PIN;
    oled_handler.Mode  = GPIO_MODE_OUTPUT_PP;
    oled_handler.Pull  = GPIO_PULLUP;
    oled_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_CON_PORT, &oled_handler);

    oled_handler.Pin   = OLED_INS_PIN;
    HAL_GPIO_Init(OLED_INS_PORT, &oled_handler);

    OLED_CON(RS, 0);delay_ms(100);OLED_CON(RS, 1);        /* 复位时序 */
    OLED_CON(RW, 1);OLED_CON(CS, 1);OLED_CON(DC, 1);      /* 控制总线复位 */

    oled_write_byte(OLED_OFF, CMD);

    oled_write_byte(OLED_ON, CMD);
}

void oled_write_byte(uint8_t con, OLED_Type typ) {

    OLED_CON(DC, typ);
    OLED_CON(CS, 0);OLED_CON(RW, 0);OLED_INS(con);OLED_CON(RW, 1);OLED_CON(CS, 1);OLED_CON(DC, 1);
}

void oled_draw_dot(uint8_t x, uint8_t y, uint8_t dot) {

    if (dot) oled_ram[x][y / 8] |= 1<<(y % 8);else oled_ram[x][y / 8] &= ~(1<<(y % 8));
}

void oled_show_uni(uint8_t x, uint8_t y, uint8_t *uni) {


}

void oled_refresh_ram(void) {

    for (uint8_t i=0;i<8;++i) {
        
        oled_write_byte(OLED_ROW + i, CMD);
        oled_write_byte(OLED_COL_LSB, CMD);oled_write_byte(OLED_COL_MSB, CMD);
        for (uint8_t j=0;j<128;++j) oled_write_byte(oled_ram[j][i], DAT);        /* 列指针会自增 */
    }
}
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

    ssd1306_init();
}

void oled_write_byte(uint8_t con, OLED_Type typ) {

    OLED_CON(DC, typ);
    OLED_CON(CS, 0);OLED_CON(RW, 0);OLED_INS(con);OLED_CON(RW, 1);OLED_CON(CS, 1);OLED_CON(DC, 1);
}

void oled_draw_dot(uint8_t x, uint8_t y, uint8_t dot) {

    if (dot) oled_ram[x][y / 8] |= 1<<(y % 8);else oled_ram[x][y / 8] &= ~(1<<(y % 8));
}

void oled_refresh_ram(void) {

    for (uint8_t i=0;i<8;++i) {
        
        oled_write_byte(OLED_ROW + i, CMD);
        oled_write_byte(OLED_COL_LSB, CMD);oled_write_byte(OLED_COL_MSB, CMD);
        for (uint8_t j=0;j<128;++j) oled_write_byte(oled_ram[j][i], DAT);        /* 列指针会自增 */
    }
}

void ssd1306_init(void) {
    
    oled_write_byte(0xAE, CMD);   /* 关闭显示 */

    oled_write_byte(0xD5, CMD);   /* 分频因子/振荡频率 */
    oled_write_byte(0x50, CMD);   /* 0~3分频因子，4~7振荡频率 */

    oled_write_byte(0xA8, CMD);   /* 扫描行数 */
    oled_write_byte(0X3F, CMD);   /* COM0~COMn */

    oled_write_byte(0xD3, CMD);   /* 显示偏移 */
    oled_write_byte(0X00, CMD);   /* 向下偏移COMn行 */

    oled_write_byte(0x40, CMD);   /* 0~5（COMn为第一行）*/

    oled_write_byte(0x8D, CMD);   /* 电荷泵 */
    oled_write_byte(0x14, CMD);   /* 位2（1:开启，0:关闭）*/

    oled_write_byte(0x20, CMD);   /* 地址模式 */
    oled_write_byte(0x02, CMD);   /* 0~1（10:页地址模式）*/

    oled_write_byte(0xA1, CMD);   /* 位0（1:从右到左，0:从左到右）*/
    oled_write_byte(0xC8, CMD);   /* 位3（1:从下到上，0:从上到下）*/

    oled_write_byte(0xDA, CMD);   /* 硬件引脚 */
    oled_write_byte(0x12, CMD);   /* 位0:引脚布局，位4:行左右交换 */

    oled_write_byte(0x81, CMD);   /* 对比度 */
    oled_write_byte(0xEF, CMD);   /* 1~0xFF（越大越亮）*/

    oled_write_byte(0xD9, CMD);   /* 预充电周期 */
    oled_write_byte(0xF1, CMD);   /* 0~3:充电时钟数，4~7:放电时钟数 */

    oled_write_byte(0xDB, CMD);   /* 电压倍率 */
    oled_write_byte(0x30, CMD);   /* 4~6（011:0.83*vcc）*/

    oled_write_byte(0xA4, CMD);   /* 全局显示，位0（1:白屏，0:黑屏）*/
    oled_write_byte(0xA6, CMD);   /* 显示方式，位0（1:反相，0:正常）*/

    oled_write_byte(0xAF, CMD);   /* 开启显示 */
}
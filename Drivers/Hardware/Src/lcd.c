#include "lcd.h"

SRAM_HandleTypeDef        lcd_init_handler;
FMC_NORSRAM_TimingTypeDef lcd_time_handler, lex_time_handler;

void lcd_init(void) {

    lcd_init_handler.Instance             = FMC_NORSRAM_DEVICE;
    lcd_init_handler.Extended             = FMC_NORSRAM_EXTENDED_DEVICE;
    lcd_init_handler.Init.NSBank          = FMC_NORSRAM_BANK1;               /* 块一 */
    lcd_init_handler.Init.MemoryType      = FMC_MEMORY_TYPE_SRAM;            /* SRAM类型 */
    lcd_init_handler.Init.ExtendedMode    = FMC_EXTENDED_MODE_ENABLE;        /* 读写异时钟 */
    lcd_init_handler.Init.WriteOperation  = FMC_WRITE_OPERATION_ENABLE;      /* 允许写操作 */
    lcd_init_handler.Init.DataAddressMux  = FMC_DATA_ADDRESS_MUX_DISABLE;    /* 地址数据线不复用 */
    lcd_init_handler.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;    /* 数据线宽度为16位*/

    lcd_time_handler.AccessMode       = FMC_ACCESS_MODE_A;   /* 模式A时序 */
    lcd_time_handler.DataSetupTime    = 86;                  /* RD低电平（355ns）*/
    lcd_time_handler.AddressSetupTime = 22;                  /* RD高电平（90ns）*/

    lex_time_handler.AccessMode       = FMC_ACCESS_MODE_A;   /* 模式A时序 */
    lex_time_handler.DataSetupTime    = 3;                   /* WR低电平（10ns）*/
    lex_time_handler.AddressSetupTime = 3;                   /* WR高电平（10ns）*/

    HAL_SRAM_Init(&lcd_init_handler, &lcd_time_handler, &lex_time_handler);ili9806g_init();LCD_BLN(1);
}

void lcd_set_cursor(uint16_t x, uint16_t y) {

    LCD->CMD = 0x2a;LCD->DAT = x>>8;LCD->DAT = x & 0xff;
    LCD->CMD = 0x2b;LCD->DAT = y>>8;LCD->DAT = y & 0xff;
}

void lcd_draw_dot(uint16_t x, uint16_t y, uint16_t dot) {

    lcd_set_cursor(x, y);LCD->CMD = 0x2c;LCD->DAT = dot;
}

uint16_t lcd_show_dot(uint16_t x, uint16_t y) {

    volatile uint16_t d, r, g, b;
    lcd_set_cursor(x, y);LCD->CMD = 0x2e;d = LCD->DAT;r = LCD->DAT;g = r & 0xff;b = LCD->DAT;
    return ((r>>11)<<11) | ((g>>2)<<5) | (b>>11);
}

void ili9806g_init(void) {

    /* 扩展指令集使能 */
    LCD->CMD = 0xFF;LCD->DAT = 0xFF;LCD->DAT = 0x98;LCD->DAT = 0x06;LCD->DAT = 0x01;

    /* GIP1：行驱动时序/映射参数 */
    LCD->CMD = 0xBC;LCD->DAT = 0x01;LCD->DAT = 0x0F;LCD->DAT = 0x61;LCD->DAT = 0xFF;LCD->DAT = 0x01;
                    LCD->DAT = 0x01;LCD->DAT = 0x0B;LCD->DAT = 0x10;LCD->DAT = 0x37;LCD->DAT = 0x63;
                    LCD->DAT = 0xFF;LCD->DAT = 0xFF;LCD->DAT = 0x01;LCD->DAT = 0x01;LCD->DAT = 0x00;
                    LCD->DAT = 0x00;LCD->DAT = 0xFF;LCD->DAT = 0x52;LCD->DAT = 0x01;LCD->DAT = 0x00;
                    LCD->DAT = 0x40;

    /* GIP2：输出顺序/相位 */
    LCD->CMD = 0xBD;LCD->DAT = 0x01;LCD->DAT = 0x23;LCD->DAT = 0x45;LCD->DAT = 0x67;LCD->DAT = 0x01;
                    LCD->DAT = 0x23;LCD->DAT = 0x45;LCD->DAT = 0x67;

    /* GIP3：门极/源极细项与偏压窗口 */
    LCD->CMD = 0xBE;LCD->DAT = 0x00;LCD->DAT = 0x01;LCD->DAT = 0xAB;LCD->DAT = 0x60;LCD->DAT = 0x22;
                    LCD->DAT = 0x22;LCD->DAT = 0x22;LCD->DAT = 0x22;LCD->DAT = 0x22;

    /* VCOM（公共电极）：对比度/残影 */
    LCD->CMD = 0xC7;LCD->DAT = 0x36;

    /* 使能 VGMP/VGMN/VGSP/VGSN */
    LCD->CMD = 0xED;LCD->DAT = 0x7F;LCD->DAT = 0x0F;

    /* 电源控制1：AVDD/AVEE/VGH/VGL */
    LCD->CMD = 0xC0;LCD->DAT = 0x0F;LCD->DAT = 0x0B;LCD->DAT = 0x0A;

    /* AVDD/AVEE由内部泵产生 */
    LCD->CMD = 0xFC;LCD->DAT = 0x08;

    /* 厂商工艺校正参数 */
    LCD->CMD = 0xDF;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x00;
                    LCD->DAT = 0x20;

    /* DVDD 数字电源档位 */
    LCD->CMD = 0xF3;LCD->DAT = 0x74;

    /* 反相模式（消水纹/闪烁相关）*/
    LCD->CMD = 0xB4;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x00;

    /* 分辨率：480×800 */
    LCD->CMD = 0xF7;LCD->DAT = 0x82;

    /* 帧率设置 */
    LCD->CMD = 0xB1;LCD->DAT = 0x00;LCD->DAT = 0x13;LCD->DAT = 0x13;

    /* 源极等化/时序细调 */
    LCD->CMD = 0xF2;LCD->DAT = 0x80;LCD->DAT = 0x04;LCD->DAT = 0x40;LCD->DAT = 0x28;

    /* 电源控制2：源驱/运放偏置、VRH、泵时钟等 */
    LCD->CMD = 0xC1;LCD->DAT = 0x17;LCD->DAT = 0x88;LCD->DAT = 0x88;LCD->DAT = 0x20;

    /* 正极Gamma表 */
    LCD->CMD = 0xE0;LCD->DAT = 0x00;LCD->DAT = 0x0A;LCD->DAT = 0x12;LCD->DAT = 0x10;LCD->DAT = 0x0E;
                    LCD->DAT = 0x20;LCD->DAT = 0xCC;LCD->DAT = 0x07;LCD->DAT = 0x06;LCD->DAT = 0x0B;
                    LCD->DAT = 0x0E;LCD->DAT = 0x0F;LCD->DAT = 0x0D;LCD->DAT = 0x15;LCD->DAT = 0x10;
                    LCD->DAT = 0x00;

    /* 负极Gamma表 */
    LCD->CMD = 0xE1;LCD->DAT = 0x00;LCD->DAT = 0x0B;LCD->DAT = 0x13;LCD->DAT = 0x0D;LCD->DAT = 0x0E;
                    LCD->DAT = 0x1B;LCD->DAT = 0x71;LCD->DAT = 0x06;LCD->DAT = 0x06;LCD->DAT = 0x0A;
                    LCD->DAT = 0x0F;LCD->DAT = 0x0E;LCD->DAT = 0x0F;LCD->DAT = 0x15;LCD->DAT = 0x0C;
                    LCD->DAT = 0x00;

    /* DCS标准指令集使能 */
    LCD->CMD = 0xFF;LCD->DAT = 0xFF;LCD->DAT = 0x98;LCD->DAT = 0x06;LCD->DAT = 0x00;
    
    /* 列地址窗口：(0x0000 ~ 0x01DF) */
    LCD->CMD = 0x2A;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x01;LCD->DAT = 0xDF;

    /* 行地址窗口：(0x0000 ~ 0x031F) */
    LCD->CMD = 0x2B;LCD->DAT = 0x00;LCD->DAT = 0x00;LCD->DAT = 0x03;LCD->DAT = 0x1F;

    /* 像素格式：RGB565 */
    LCD->CMD = 0x3A;LCD->DAT = 0x55;

    /* BGR位，横竖屏（翻转可尝试 0x02/0x03/0xC0）*/
    LCD->CMD = 0x36;LCD->DAT = 0x00;

    /* 退出休眠并显示 */
    LCD->CMD = 0x11;delay_ms(120);LCD->CMD = 0x29;
}
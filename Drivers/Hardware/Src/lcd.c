#include "lcd.h"

LCD_CON                   lcd;
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
    lcd_time_handler.DataSetupTime    = 81;                  /* RD低电平（335ns）*/
    lcd_time_handler.AddressSetupTime = 22;                  /* RD高电平（90ns）*/

    lex_time_handler.AccessMode       = FMC_ACCESS_MODE_A;   /* 模式A时序 */
    lex_time_handler.DataSetupTime    = 4;                   /* WR低电平（15ns）*/
    lex_time_handler.AddressSetupTime = 4;                   /* WR高电平（15ns）*/

    HAL_SRAM_Init(&lcd_init_handler, &lcd_time_handler, &lex_time_handler);
    nt35510_init();
}

void lcd_set_cursor(uint16_t x, uint16_t y) {

    LCD->CMD = lcd.x;LCD->DAT = x>>8;LCD->DAT = x & 0x00ff;
    LCD->CMD = lcd.y;LCD->DAT = y>>8;LCD->DAT = y & 0x00ff;
}

void lcd_draw_dot(uint16_t x, uint16_t y, uint16_t dot) {

    lcd_set_cursor(x, y);LCD->CMD = lcd.g;LCD->DAT = dot;
}

uint16_t lcd_show_dot(uint16_t x, uint16_t y) {

    uint16_t d, r, g, b;
    lcd_set_cursor(x, y);LCD->CMD = 0x2e;d = LCD->DAT;r = LCD->DAT;g = r & 0x00ff;b = LCD->DAT;
    return ((r>>11)<<11) | ((g>>2)<<5) | (b>>11);
}

void nt35510_init(void) {

    /* 解锁Level2 Page1 */
    LCD->CMD = 0xF000; LCD->DAT = 0x0055;
    LCD->CMD = 0xF001; LCD->DAT = 0x00AA;
    LCD->CMD = 0xF002; LCD->DAT = 0x0052;
    LCD->CMD = 0xF003; LCD->DAT = 0x0008;
    LCD->CMD = 0xF004; LCD->DAT = 0x0001;  /* Page = 1 */

    /* AVDD 5.2V 源极驱动放大电压 */
    LCD->CMD = 0xB000; LCD->DAT = 0x000D;
    LCD->CMD = 0xB001; LCD->DAT = 0x000D;
    LCD->CMD = 0xB002; LCD->DAT = 0x000D;

    LCD->CMD = 0xB600; LCD->DAT = 0x0034;  /* AVDD 电荷泵倍压/抽头（下同）*/
    LCD->CMD = 0xB601; LCD->DAT = 0x0034;
    LCD->CMD = 0xB602; LCD->DAT = 0x0034;

    /* AVEE -5.2V 源极负压对称电压 */
    LCD->CMD = 0xB100; LCD->DAT = 0x000D;
    LCD->CMD = 0xB101; LCD->DAT = 0x000D;
    LCD->CMD = 0xB102; LCD->DAT = 0x000D;

    LCD->CMD = 0xB700; LCD->DAT = 0x0034;
    LCD->CMD = 0xB701; LCD->DAT = 0x0034;
    LCD->CMD = 0xB702; LCD->DAT = 0x0034;

    /* VCL -2.5V 中间负压层 */
    LCD->CMD = 0xB200; LCD->DAT = 0x0000;
    LCD->CMD = 0xB201; LCD->DAT = 0x0000;
    LCD->CMD = 0xB202; LCD->DAT = 0x0000;

    LCD->CMD = 0xB800; LCD->DAT = 0x0024;
    LCD->CMD = 0xB801; LCD->DAT = 0x0024;
    LCD->CMD = 0xB802; LCD->DAT = 0x0024;

    /* VGH 15V 栅极"开门"电压 */ 
    LCD->CMD = 0xBF00; LCD->DAT = 0x0001;
    LCD->CMD = 0xB300; LCD->DAT = 0x000F;
    LCD->CMD = 0xB301; LCD->DAT = 0x000F;
    LCD->CMD = 0xB302; LCD->DAT = 0x000F;

    LCD->CMD = 0xB900; LCD->DAT = 0x0034;
    LCD->CMD = 0xB901; LCD->DAT = 0x0034;
    LCD->CMD = 0xB902; LCD->DAT = 0x0034;

    /* VGL -10V 栅极"关门"电压 */
    LCD->CMD = 0xB500; LCD->DAT = 0x0008;
    LCD->CMD = 0xB501; LCD->DAT = 0x0008;
    LCD->CMD = 0xB502; LCD->DAT = 0x0008;
    LCD->CMD = 0xC200; LCD->DAT = 0x0003;

    LCD->CMD = 0xBA00; LCD->DAT = 0x0024;
    LCD->CMD = 0xBA01; LCD->DAT = 0x0024;
    LCD->CMD = 0xBA02; LCD->DAT = 0x0024;

    /* VGMP/VGSP 4.5V/0V 源极灰阶正端 */
    LCD->CMD = 0xBC00; LCD->DAT = 0x0000;
    LCD->CMD = 0xBC01; LCD->DAT = 0x0078;
    LCD->CMD = 0xBC02; LCD->DAT = 0x0000;

    /* VGMN/VGSN -4.5V/0V 源极灰阶负端 */
    LCD->CMD = 0xBD00; LCD->DAT = 0x0000;
    LCD->CMD = 0xBD01; LCD->DAT = 0x0078;
    LCD->CMD = 0xBD02; LCD->DAT = 0x0000;

    /* VCOM 公共电极（液晶基板中点）*/
    LCD->CMD = 0xBE00; LCD->DAT = 0x0000;
    LCD->CMD = 0xBE01; LCD->DAT = 0x0064;

    /* Gamma: D1 (R+) */
    LCD->CMD = 0xD100; LCD->DAT = 0x0000;
    LCD->CMD = 0xD101; LCD->DAT = 0x0033;
    LCD->CMD = 0xD102; LCD->DAT = 0x0000;
    LCD->CMD = 0xD103; LCD->DAT = 0x0034;
    LCD->CMD = 0xD104; LCD->DAT = 0x0000;
    LCD->CMD = 0xD105; LCD->DAT = 0x003A;
    LCD->CMD = 0xD106; LCD->DAT = 0x0000;
    LCD->CMD = 0xD107; LCD->DAT = 0x004A;
    LCD->CMD = 0xD108; LCD->DAT = 0x0000;
    LCD->CMD = 0xD109; LCD->DAT = 0x005C;
    LCD->CMD = 0xD10A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD10B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD10C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD10D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD10E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD10F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD110; LCD->DAT = 0x0001;
    LCD->CMD = 0xD111; LCD->DAT = 0x0013;
    LCD->CMD = 0xD112; LCD->DAT = 0x0001;
    LCD->CMD = 0xD113; LCD->DAT = 0x0054;
    LCD->CMD = 0xD114; LCD->DAT = 0x0001;
    LCD->CMD = 0xD115; LCD->DAT = 0x0082;
    LCD->CMD = 0xD116; LCD->DAT = 0x0001;
    LCD->CMD = 0xD117; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD118; LCD->DAT = 0x0002;
    LCD->CMD = 0xD119; LCD->DAT = 0x0000;
    LCD->CMD = 0xD11A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD11B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD11C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD11D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD11E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD11F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD120; LCD->DAT = 0x0002;
    LCD->CMD = 0xD121; LCD->DAT = 0x0084;
    LCD->CMD = 0xD122; LCD->DAT = 0x0002;
    LCD->CMD = 0xD123; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD124; LCD->DAT = 0x0002;
    LCD->CMD = 0xD125; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD126; LCD->DAT = 0x0002;
    LCD->CMD = 0xD127; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD128; LCD->DAT = 0x0002;
    LCD->CMD = 0xD129; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD12A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD12B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD12C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD12D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD12E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD12F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD130; LCD->DAT = 0x0003;
    LCD->CMD = 0xD131; LCD->DAT = 0x0033;
    LCD->CMD = 0xD132; LCD->DAT = 0x0003;
    LCD->CMD = 0xD133; LCD->DAT = 0x006D;

    /* Gamma: D2 (G+) */
    LCD->CMD = 0xD200; LCD->DAT = 0x0000;
    LCD->CMD = 0xD201; LCD->DAT = 0x0033;
    LCD->CMD = 0xD202; LCD->DAT = 0x0000;
    LCD->CMD = 0xD203; LCD->DAT = 0x0034;
    LCD->CMD = 0xD204; LCD->DAT = 0x0000;
    LCD->CMD = 0xD205; LCD->DAT = 0x003A;
    LCD->CMD = 0xD206; LCD->DAT = 0x0000;
    LCD->CMD = 0xD207; LCD->DAT = 0x004A;
    LCD->CMD = 0xD208; LCD->DAT = 0x0000;
    LCD->CMD = 0xD209; LCD->DAT = 0x005C;
    LCD->CMD = 0xD20A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD20B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD20C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD20D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD20E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD20F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD210; LCD->DAT = 0x0001;
    LCD->CMD = 0xD211; LCD->DAT = 0x0013;
    LCD->CMD = 0xD212; LCD->DAT = 0x0001;
    LCD->CMD = 0xD213; LCD->DAT = 0x0054;
    LCD->CMD = 0xD214; LCD->DAT = 0x0001;
    LCD->CMD = 0xD215; LCD->DAT = 0x0082;
    LCD->CMD = 0xD216; LCD->DAT = 0x0001;
    LCD->CMD = 0xD217; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD218; LCD->DAT = 0x0002;
    LCD->CMD = 0xD219; LCD->DAT = 0x0000;
    LCD->CMD = 0xD21A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD21B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD21C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD21D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD21E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD21F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD220; LCD->DAT = 0x0002;
    LCD->CMD = 0xD221; LCD->DAT = 0x0084;
    LCD->CMD = 0xD222; LCD->DAT = 0x0002;
    LCD->CMD = 0xD223; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD224; LCD->DAT = 0x0002;
    LCD->CMD = 0xD225; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD226; LCD->DAT = 0x0002;
    LCD->CMD = 0xD227; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD228; LCD->DAT = 0x0002;
    LCD->CMD = 0xD229; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD22A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD22B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD22C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD22D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD22E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD22F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD230; LCD->DAT = 0x0003;
    LCD->CMD = 0xD231; LCD->DAT = 0x0033;
    LCD->CMD = 0xD232; LCD->DAT = 0x0003;
    LCD->CMD = 0xD233; LCD->DAT = 0x006D;

    /* Gamma: D3 (B+) */
    LCD->CMD = 0xD300; LCD->DAT = 0x0000;
    LCD->CMD = 0xD301; LCD->DAT = 0x0033;
    LCD->CMD = 0xD302; LCD->DAT = 0x0000;
    LCD->CMD = 0xD303; LCD->DAT = 0x0034;
    LCD->CMD = 0xD304; LCD->DAT = 0x0000;
    LCD->CMD = 0xD305; LCD->DAT = 0x003A;
    LCD->CMD = 0xD306; LCD->DAT = 0x0000;
    LCD->CMD = 0xD307; LCD->DAT = 0x004A;
    LCD->CMD = 0xD308; LCD->DAT = 0x0000;
    LCD->CMD = 0xD309; LCD->DAT = 0x005C;
    LCD->CMD = 0xD30A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD30B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD30C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD30D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD30E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD30F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD310; LCD->DAT = 0x0001;
    LCD->CMD = 0xD311; LCD->DAT = 0x0013;
    LCD->CMD = 0xD312; LCD->DAT = 0x0001;
    LCD->CMD = 0xD313; LCD->DAT = 0x0054;
    LCD->CMD = 0xD314; LCD->DAT = 0x0001;
    LCD->CMD = 0xD315; LCD->DAT = 0x0082;
    LCD->CMD = 0xD316; LCD->DAT = 0x0001;
    LCD->CMD = 0xD317; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD318; LCD->DAT = 0x0002;
    LCD->CMD = 0xD319; LCD->DAT = 0x0000;
    LCD->CMD = 0xD31A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD31B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD31C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD31D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD31E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD31F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD320; LCD->DAT = 0x0002;
    LCD->CMD = 0xD321; LCD->DAT = 0x0084;
    LCD->CMD = 0xD322; LCD->DAT = 0x0002;
    LCD->CMD = 0xD323; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD324; LCD->DAT = 0x0002;
    LCD->CMD = 0xD325; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD326; LCD->DAT = 0x0002;
    LCD->CMD = 0xD327; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD328; LCD->DAT = 0x0002;
    LCD->CMD = 0xD329; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD32A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD32B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD32C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD32D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD32E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD32F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD330; LCD->DAT = 0x0003;
    LCD->CMD = 0xD331; LCD->DAT = 0x0033;
    LCD->CMD = 0xD332; LCD->DAT = 0x0003;
    LCD->CMD = 0xD333; LCD->DAT = 0x006D;

    /* Gamma: D4 (R-) */
    LCD->CMD = 0xD400; LCD->DAT = 0x0000;
    LCD->CMD = 0xD401; LCD->DAT = 0x0033;
    LCD->CMD = 0xD402; LCD->DAT = 0x0000;
    LCD->CMD = 0xD403; LCD->DAT = 0x0034;
    LCD->CMD = 0xD404; LCD->DAT = 0x0000;
    LCD->CMD = 0xD405; LCD->DAT = 0x003A;
    LCD->CMD = 0xD406; LCD->DAT = 0x0000;
    LCD->CMD = 0xD407; LCD->DAT = 0x004A;
    LCD->CMD = 0xD408; LCD->DAT = 0x0000;
    LCD->CMD = 0xD409; LCD->DAT = 0x005C;
    LCD->CMD = 0xD40A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD40B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD40C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD40D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD40E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD40F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD410; LCD->DAT = 0x0001;
    LCD->CMD = 0xD411; LCD->DAT = 0x0013;
    LCD->CMD = 0xD412; LCD->DAT = 0x0001;
    LCD->CMD = 0xD413; LCD->DAT = 0x0054;
    LCD->CMD = 0xD414; LCD->DAT = 0x0001;
    LCD->CMD = 0xD415; LCD->DAT = 0x0082;
    LCD->CMD = 0xD416; LCD->DAT = 0x0001;
    LCD->CMD = 0xD417; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD418; LCD->DAT = 0x0002;
    LCD->CMD = 0xD419; LCD->DAT = 0x0000;
    LCD->CMD = 0xD41A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD41B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD41C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD41D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD41E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD41F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD420; LCD->DAT = 0x0002;
    LCD->CMD = 0xD421; LCD->DAT = 0x0084;
    LCD->CMD = 0xD422; LCD->DAT = 0x0002;
    LCD->CMD = 0xD423; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD424; LCD->DAT = 0x0002;
    LCD->CMD = 0xD425; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD426; LCD->DAT = 0x0002;
    LCD->CMD = 0xD427; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD428; LCD->DAT = 0x0002;
    LCD->CMD = 0xD429; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD42A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD42B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD42C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD42D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD42E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD42F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD430; LCD->DAT = 0x0003;
    LCD->CMD = 0xD431; LCD->DAT = 0x0033;
    LCD->CMD = 0xD432; LCD->DAT = 0x0003;
    LCD->CMD = 0xD433; LCD->DAT = 0x006D;

    /* Gamma: D5 (G-) */
    LCD->CMD = 0xD500; LCD->DAT = 0x0000;
    LCD->CMD = 0xD501; LCD->DAT = 0x0033;
    LCD->CMD = 0xD502; LCD->DAT = 0x0000;
    LCD->CMD = 0xD503; LCD->DAT = 0x0034;
    LCD->CMD = 0xD504; LCD->DAT = 0x0000;
    LCD->CMD = 0xD505; LCD->DAT = 0x003A;
    LCD->CMD = 0xD506; LCD->DAT = 0x0000;
    LCD->CMD = 0xD507; LCD->DAT = 0x004A;
    LCD->CMD = 0xD508; LCD->DAT = 0x0000;
    LCD->CMD = 0xD509; LCD->DAT = 0x005C;
    LCD->CMD = 0xD50A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD50B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD50C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD50D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD50E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD50F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD510; LCD->DAT = 0x0001;
    LCD->CMD = 0xD511; LCD->DAT = 0x0013;
    LCD->CMD = 0xD512; LCD->DAT = 0x0001;
    LCD->CMD = 0xD513; LCD->DAT = 0x0054;
    LCD->CMD = 0xD514; LCD->DAT = 0x0001;
    LCD->CMD = 0xD515; LCD->DAT = 0x0082;
    LCD->CMD = 0xD516; LCD->DAT = 0x0001;
    LCD->CMD = 0xD517; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD518; LCD->DAT = 0x0002;
    LCD->CMD = 0xD519; LCD->DAT = 0x0000;
    LCD->CMD = 0xD51A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD51B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD51C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD51D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD51E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD51F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD520; LCD->DAT = 0x0002;
    LCD->CMD = 0xD521; LCD->DAT = 0x0084;
    LCD->CMD = 0xD522; LCD->DAT = 0x0002;
    LCD->CMD = 0xD523; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD524; LCD->DAT = 0x0002;
    LCD->CMD = 0xD525; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD526; LCD->DAT = 0x0002;
    LCD->CMD = 0xD527; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD528; LCD->DAT = 0x0002;
    LCD->CMD = 0xD529; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD52A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD52B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD52C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD52D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD52E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD52F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD530; LCD->DAT = 0x0003;
    LCD->CMD = 0xD531; LCD->DAT = 0x0033;
    LCD->CMD = 0xD532; LCD->DAT = 0x0003;
    LCD->CMD = 0xD533; LCD->DAT = 0x006D;

    /* Gamma: D6 (B-) */
    LCD->CMD = 0xD600; LCD->DAT = 0x0000;
    LCD->CMD = 0xD601; LCD->DAT = 0x0033;
    LCD->CMD = 0xD602; LCD->DAT = 0x0000;
    LCD->CMD = 0xD603; LCD->DAT = 0x0034;
    LCD->CMD = 0xD604; LCD->DAT = 0x0000;
    LCD->CMD = 0xD605; LCD->DAT = 0x003A;
    LCD->CMD = 0xD606; LCD->DAT = 0x0000;
    LCD->CMD = 0xD607; LCD->DAT = 0x004A;
    LCD->CMD = 0xD608; LCD->DAT = 0x0000;
    LCD->CMD = 0xD609; LCD->DAT = 0x005C;
    LCD->CMD = 0xD60A; LCD->DAT = 0x0000;
    LCD->CMD = 0xD60B; LCD->DAT = 0x0081;
    LCD->CMD = 0xD60C; LCD->DAT = 0x0000;
    LCD->CMD = 0xD60D; LCD->DAT = 0x00A6;
    LCD->CMD = 0xD60E; LCD->DAT = 0x0000;
    LCD->CMD = 0xD60F; LCD->DAT = 0x00E5;
    LCD->CMD = 0xD610; LCD->DAT = 0x0001;
    LCD->CMD = 0xD611; LCD->DAT = 0x0013;
    LCD->CMD = 0xD612; LCD->DAT = 0x0001;
    LCD->CMD = 0xD613; LCD->DAT = 0x0054;
    LCD->CMD = 0xD614; LCD->DAT = 0x0001;
    LCD->CMD = 0xD615; LCD->DAT = 0x0082;
    LCD->CMD = 0xD616; LCD->DAT = 0x0001;
    LCD->CMD = 0xD617; LCD->DAT = 0x00CA;
    LCD->CMD = 0xD618; LCD->DAT = 0x0002;
    LCD->CMD = 0xD619; LCD->DAT = 0x0000;
    LCD->CMD = 0xD61A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD61B; LCD->DAT = 0x0001;
    LCD->CMD = 0xD61C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD61D; LCD->DAT = 0x0034;
    LCD->CMD = 0xD61E; LCD->DAT = 0x0002;
    LCD->CMD = 0xD61F; LCD->DAT = 0x0067;
    LCD->CMD = 0xD620; LCD->DAT = 0x0002;
    LCD->CMD = 0xD621; LCD->DAT = 0x0084;
    LCD->CMD = 0xD622; LCD->DAT = 0x0002;
    LCD->CMD = 0xD623; LCD->DAT = 0x00A4;
    LCD->CMD = 0xD624; LCD->DAT = 0x0002;
    LCD->CMD = 0xD625; LCD->DAT = 0x00B7;
    LCD->CMD = 0xD626; LCD->DAT = 0x0002;
    LCD->CMD = 0xD627; LCD->DAT = 0x00CF;
    LCD->CMD = 0xD628; LCD->DAT = 0x0002;
    LCD->CMD = 0xD629; LCD->DAT = 0x00DE;
    LCD->CMD = 0xD62A; LCD->DAT = 0x0002;
    LCD->CMD = 0xD62B; LCD->DAT = 0x00F2;
    LCD->CMD = 0xD62C; LCD->DAT = 0x0002;
    LCD->CMD = 0xD62D; LCD->DAT = 0x00FE;
    LCD->CMD = 0xD62E; LCD->DAT = 0x0003;
    LCD->CMD = 0xD62F; LCD->DAT = 0x0010;
    LCD->CMD = 0xD630; LCD->DAT = 0x0003;
    LCD->CMD = 0xD631; LCD->DAT = 0x0033;
    LCD->CMD = 0xD632; LCD->DAT = 0x0003;
    LCD->CMD = 0xD633; LCD->DAT = 0x006D;

    /* 解锁Level2 Page0 */
    LCD->CMD = 0xF000; LCD->DAT = 0x0055;
    LCD->CMD = 0xF001; LCD->DAT = 0x00AA;
    LCD->CMD = 0xF002; LCD->DAT = 0x0052;
    LCD->CMD = 0xF003; LCD->DAT = 0x0008;
    LCD->CMD = 0xF004; LCD->DAT = 0x0000;

    /* 显示控制和时序 */
    LCD->CMD = 0xB100; LCD->DAT = 0x00CC;
    LCD->CMD = 0xB101; LCD->DAT = 0x0000;

    LCD->CMD = 0xB600; LCD->DAT = 0x0005;  /* 源极保持时间 */

    LCD->CMD = 0xB700; LCD->DAT = 0x0070;  /* 栅极均衡 */
    LCD->CMD = 0xB701; LCD->DAT = 0x0070;

    LCD->CMD = 0xB800; LCD->DAT = 0x0001;  /* 源极均衡模式 */
    LCD->CMD = 0xB801; LCD->DAT = 0x0003;
    LCD->CMD = 0xB802; LCD->DAT = 0x0003;
    LCD->CMD = 0xB803; LCD->DAT = 0x0003;

    LCD->CMD = 0xBC00; LCD->DAT = 0x0002;  /* 反相模式 */
    LCD->CMD = 0xBC01; LCD->DAT = 0x0000;
    LCD->CMD = 0xBC02; LCD->DAT = 0x0000;

    LCD->CMD = 0xC900; LCD->DAT = 0x00D0;  /* 延时相位 */
    LCD->CMD = 0xC901; LCD->DAT = 0x0002;
    LCD->CMD = 0xC902; LCD->DAT = 0x0050;
    LCD->CMD = 0xC903; LCD->DAT = 0x0050;
    LCD->CMD = 0xC904; LCD->DAT = 0x0050;

    /* 撕裂信号和像素格式 */
    LCD->CMD = 0x3500; LCD->DAT = 0x0000;  /* 垂直回归 */
    LCD->CMD = 0x3A00; LCD->DAT = 0x0055;  /* RGB565（兼容MCU，RGB接口）*/

    /* 访问控制 */
    LCD->CMD = 0x3600; LCD->DAT = 0x0008;  /* MY,MX,MV = 000，从左到右，从上到下
                                              BGR = 1，红色在前，蓝色在后 */

    /* 屏幕分辨率 */
    LCD->CMD = 0x2A00; LCD->DAT = 0x0000;  /* X start MSB */
    LCD->CMD = 0x2A01; LCD->DAT = 0x0000;  /* X start LSB */
    LCD->CMD = 0x2A02; LCD->DAT = 0x0001;  /* X end   MSB (0x01DF) */
    LCD->CMD = 0x2A03; LCD->DAT = 0x00DF;  /* X end   LSB (479) */
    LCD->CMD = 0x2B00; LCD->DAT = 0x0000;  /* Y start MSB */
    LCD->CMD = 0x2B01; LCD->DAT = 0x0000;  /* Y start LSB */
    LCD->CMD = 0x2B02; LCD->DAT = 0x0003;  /* Y end   MSB (0x031F) */
    LCD->CMD = 0x2B03; LCD->DAT = 0x001F;  /* Y end   LSB (799) */

    /* 显示 */
    LCD->CMD = 0x1100;  /* 退出睡眠模式 */
    delay_us(120);
    LCD->CMD = 0x2900;  /* 开始显示图像 */
}
#include "rgb.h"

uint16_t             rgb_ram[180][260] __attribute__((section(".sdram")));
LTDC_HandleTypeDef   rgb_init_handler;
LTDC_LayerCfgTypeDef rgb_layer_handler;

void rgb_init(void) {

    rgb_init_handler.Instance                = LTDC;
    rgb_init_handler.Init.HSPolarity         = LTDC_HSPOLARITY_AL;      /* 水平同步极性（VS）*/
    rgb_init_handler.Init.VSPolarity         = LTDC_VSPOLARITY_AL;      /* 垂直同步极性（HS）*/
    rgb_init_handler.Init.DEPolarity         = LTDC_DEPOLARITY_AL;      /* 数据使能极性（DE）*/
    rgb_init_handler.Init.PCPolarity         = LTDC_PCPOLARITY_IPC;     /* 像素时钟边沿（CLK，上升沿）*/
    rgb_init_handler.Init.HorizontalSync     = 48 - 1;                  /* 水平同步宽度（HS）*/
    rgb_init_handler.Init.AccumulatedHBP     = 48 + 88 - 1;             /* 水平后廊宽度（HS+DE）*/
    rgb_init_handler.Init.AccumulatedActiveW = 48 + 88 + 800 - 1;       /* 行数据有效字（HS+DE+DE）*/
    rgb_init_handler.Init.TotalWidth         = 48 + 88 + 800 + 40 - 1;  /* 水平前廊宽度（HS+DE+DE+DE）*/
    rgb_init_handler.Init.VerticalSync       = 3 - 1;                   /* 垂直同步宽度（VS）*/
    rgb_init_handler.Init.AccumulatedVBP     = 3 + 32 - 1;              /* 垂直后廊宽度（VS+DE）*/
    rgb_init_handler.Init.AccumulatedActiveH = 3 + 32 + 480 - 1;        /* 帧数据有效行（VS+DE+DE）*/
    rgb_init_handler.Init.TotalHeigh         = 3 + 32 + 480 + 13 - 1;   /* 垂直前廊宽度（VS+DE+DE+DE）*/
    rgb_init_handler.Init.Backcolor.Red      = 0;                       /* 背景层 */
    rgb_init_handler.Init.Backcolor.Green    = 0xff;                    /* RGB888 */
    rgb_init_handler.Init.Backcolor.Blue     = 0;                       /* 0x00ff00 */
    HAL_LTDC_Init(&rgb_init_handler);

    rgb_layer_handler.WindowX0        = 200;                       /* 层左边界 */
    rgb_layer_handler.WindowX1        = 200 + 400;                 /* 层右边界（开区间）*/
    rgb_layer_handler.WindowY0        = 120;                       /* 层上边界 */
    rgb_layer_handler.WindowY1        = 120 + 240;                 /* 层下边界（开区间）*/
    rgb_layer_handler.PixelFormat     = LTDC_PIXEL_FORMAT_RGB565;  /* 像素格式 */
    rgb_layer_handler.Alpha           = 0xff;                      /* 恒定Alpha */
    rgb_layer_handler.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;  /* 层混合系数1 */
    rgb_layer_handler.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;  /* 层混合系数2 */
    rgb_layer_handler.FBStartAdress   = (uint32_t)rgb_ram;         /* 显存起始地址 */
    rgb_layer_handler.ImageWidth      = 260;                       /* 显存行长 */
    rgb_layer_handler.ImageHeight     = 180;                       /* 显存列长 */
    rgb_layer_handler.Alpha0          = 0xff;                      /* 默认Alpha */
    rgb_layer_handler.Backcolor.Red   = 0xff;                      /* 默认层色 */
    rgb_layer_handler.Backcolor.Green = 0;                         /* RGB888 */
    rgb_layer_handler.Backcolor.Blue  = 0;                         /* 0xff0000 */
    HAL_LTDC_ConfigLayer(&rgb_init_handler, &rgb_layer_handler, 0);RGB_BLN(1);
}

void rgb_draw_dot(uint16_t x, uint16_t y, uint16_t dot) {

    if (RGB_MODE) rgb_ram[479 - x][y] = dot;else rgb_ram[y][x] = dot;
}

uint16_t rgb_show_dot(uint16_t x, uint16_t y) {

    if (RGB_MODE) return rgb_ram[479 - x][y];else return rgb_ram[y][x];
}
#include "rgb.h"

uint32_t             addr, size, offs;
uint16_t             rgb_ram[RGB_HEIGHT][RGB_WIDTH] __attribute__((section(".sdram")));
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

    rgb_layer_handler.WindowX0        = RGB_WINDOW_XS;                /* 窗口左边界 */
    rgb_layer_handler.WindowX1        = RGB_WINDOW_XE;                /* 窗口右边界（开区间）*/
    rgb_layer_handler.WindowY0        = RGB_WINDOW_YS;                /* 窗口上边界 */
    rgb_layer_handler.WindowY1        = RGB_WINDOW_YE;                /* 窗口下边界（开区间）*/
    rgb_layer_handler.PixelFormat     = LTDC_PIXEL_FORMAT_RGB565;     /* 像素格式 */
    rgb_layer_handler.Alpha           = 0xff;                         /* 恒定Alpha */
    rgb_layer_handler.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;  /* 层混合系数1 */
    rgb_layer_handler.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;  /* 层混合系数2 */
    rgb_layer_handler.FBStartAdress   = (uint32_t)rgb_ram;            /* 显存起始地址 */
    rgb_layer_handler.ImageWidth      = RGB_WIDTH;                    /* 显存行长 */
    rgb_layer_handler.ImageHeight     = RGB_HEIGHT;                   /* 显存列长 */
    rgb_layer_handler.Alpha0          = 0x00;                         /* 默认Alpha */
    rgb_layer_handler.Backcolor.Red   = 0;                            /* 默认层色 */
    rgb_layer_handler.Backcolor.Green = 0;                            /* RGB888 */
    rgb_layer_handler.Backcolor.Blue  = 0xff;                         /* 0x0000ff */
    HAL_LTDC_ConfigLayer(&rgb_init_handler, &rgb_layer_handler, 0);RGB_BLN(1);
}

void rgb_draw_dot(uint16_t x, uint16_t y, uint16_t dot) {

    if (RGB_MODE) rgb_ram[RGB_HEIGHT - 1 - x][y] = dot;else rgb_ram[y][x] = dot;
}

uint16_t rgb_show_dot(uint16_t x, uint16_t y) {

    if (RGB_MODE) return rgb_ram[RGB_HEIGHT - 1 - x][y];else return rgb_ram[y][x];
}

void rgb_reco_area(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye) {

    if (RGB_MODE) {

        addr = (uint32_t)rgb_ram[RGB_HEIGHT - 1 - xe] + 2 * ys; 
        size = ((ye - ys + 1)<<16) | (xe - xs + 1);
        offs = RGB_WIDTH - (ye - ys + 1);

    } else {

        addr = (uint32_t)rgb_ram[ys] + 2 * xs;
        size = ((xe - xs + 1)<<16) | (ye - ys + 1);
        offs = RGB_WIDTH - (xe - xs + 1);
    }
}

void rgb_draw_area(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t area) {

    rgb_reco_area(xs, xe, ys, ye);
    DMA2D -> CR     &= ~DMA2D_CR_START;       /* 停止DMA2D */
    DMA2D -> CR     = DMA2D_R2M;              /* 寄存器到存储器 */
    DMA2D -> OCOLR  = (uint32_t)area;         /* 输出颜色 */
    DMA2D -> OPFCCR = DMA2D_OUTPUT_RGB565;    /* 输出颜色格式 */
    DMA2D -> OMAR   = addr;                   /* 输出地址 */
    DMA2D -> NLR    = size;                   /* 大小 */
    DMA2D -> OOR    = offs;                   /* 输出偏移 */
    DMA2D -> CR     |= DMA2D_CR_START;        /* 开启DMA2D */
    while (!(DMA2D -> ISR & DMA2D_FLAG_TC));  /* 等待传输完成 */
    DMA2D -> IFCR   |= DMA2D_FLAG_TC;         /* 清中断标志位 */
}

void rgb_draw_picture(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint32_t picture) {

    rgb_reco_area(xs, xe, ys, ye);
    DMA2D -> CR      &= ~DMA2D_CR_START;      /* 停止DMA2D */
    DMA2D -> CR      = DMA2D_M2M;             /* 存储器到存储器 */
    DMA2D -> FGPFCCR = DMA2D_INPUT_RGB565;    /* 输入颜色格式（前景层）*/
    DMA2D -> OPFCCR  = DMA2D_OUTPUT_RGB565;   /* 输出颜色格式 */
    DMA2D -> FGMAR   = picture;               /* 输入地址（前景层）*/
    DMA2D -> OMAR    = addr;                  /* 输出地址 */
    DMA2D -> NLR     = size;                  /* 大小 */
    DMA2D -> FGOR    = 0;                     /* 输入偏移（前景层）*/
    DMA2D -> OOR     = offs;                  /* 输出偏移 */
    DMA2D -> CR      |= DMA2D_CR_START;       /* 开启DMA2D */
    while (!(DMA2D -> ISR & DMA2D_FLAG_TC));  /* 等待传输完成 */
    DMA2D -> IFCR    |= DMA2D_FLAG_TC;        /* 清中断标志位 */
}
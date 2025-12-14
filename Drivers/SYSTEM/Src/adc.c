#include "adc.h"

uint8_t           adc_stat;
uint16_t          dat[ADC_PAD] __attribute__((aligned(32)));
uint32_t          off[ADC_CHANNEL];
ADC_HandleTypeDef adc_init_handler;
DMA_HandleTypeDef adc_dma_handler;
TIM_HandleTypeDef adc_time_handler;

void adc_init(void) {

    adc_init_handler.Instance = ADC;
    adc_init_handler.Init.ClockPrescaler           = ADC_CLOCK_ASYNC_DIV1;            /* PLL3R */
    adc_init_handler.Init.Resolution               = ADC_RESOLUTION_16B;              /* 16位分辨率 */
    adc_init_handler.Init.LeftBitShift             = ADC_LEFTBITSHIFT_NONE;           /* 数据右对齐 */
    adc_init_handler.Init.EOCSelection             = ADC_EOC_SINGLE_CONV;             /* EOC置位时机 */
    adc_init_handler.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR; /* DMA循环读取 */
    adc_init_handler.Init.Overrun                  = ADC_OVR_DATA_PRESERVED;          /* 数据溢出不覆盖 */
    adc_init_handler.Init.LowPowerAutoWait         = ENABLE;                          /* 低功耗等待完成 */
    adc_init_handler.Init.ExternalTrigConv         = ADC_EXTERNALTRIG_T4_TRGO;        /* TIM4的TRGO */
    adc_init_handler.Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_RISING; /* 上升沿触发 */   
    adc_init_handler.Init.ScanConvMode             = ADC_SCAN_ENABLE;                 /* 扫描模式 */
    adc_init_handler.Init.ContinuousConvMode       = DISABLE;                         /* 单次转换 */
    adc_init_handler.Init.NbrOfConversion          = ADC_CHANNEL;                     /* 规则组5通道 */
    adc_init_handler.Init.DiscontinuousConvMode    = DISABLE;                         /* 非间断模式 */
    adc_init_handler.Init.NbrOfDiscConversion      = 0;                               /* 间断规则组0通道 */
    adc_init_handler.Init.OversamplingMode         = DISABLE;                         /* 过采样模式 */
    adc_init_handler.Init.Oversampling.Ratio                 =
    adc_init_handler.Init.Oversampling.RightBitShift         =
    adc_init_handler.Init.Oversampling.TriggeredMode         =
    adc_init_handler.Init.Oversampling.OversamplingStopReset =
    HAL_ADC_Init(&adc_init_handler);
    HAL_ADCEx_Calibration_Start(&adc_init_handler, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);  /* 偏移校准，单端模式 */

    adc_config_channel(ADC_CHANNEL_17, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_387CYCLES_5);off[0] = 0;
    adc_config_channel(ADC_CHANNEL_14, ADC_REGULAR_RANK_2, ADC_SAMPLETIME_387CYCLES_5);off[1] = 0;
    adc_config_channel(ADC_CHANNEL_15, ADC_REGULAR_RANK_3, ADC_SAMPLETIME_387CYCLES_5);off[2] = 0;
    adc_config_channel(ADC_CHANNEL_18, ADC_REGULAR_RANK_4, ADC_SAMPLETIME_387CYCLES_5);off[3] = 0;
    adc_config_channel(ADC_CHANNEL_7,  ADC_REGULAR_RANK_5, ADC_SAMPLETIME_387CYCLES_5);off[4] = 0;

    HAL_ADC_Start_DMA(&adc_init_handler, (uint32_t *)dat, ADC_SIZE);
    HAL_TIM_Base_Start(&adc_time_handler);  /* 定时器最后开启 */
}

void adc_config_channel(uint32_t cha, uint32_t ran, uint32_t sam) {

    ADC_ChannelConfTypeDef adc_conf_handler;

    adc_conf_handler.Channel                = cha;                 /* 通道号 */
    adc_conf_handler.Rank                   = ran;                 /* 通道排序 */
    adc_conf_handler.SamplingTime           = sam;                 /* 采样时间 */
    adc_conf_handler.SingleDiff             = ADC_SINGLE_ENDED;    /* 单端模式 */
    adc_conf_handler.OffsetNumber           = ADC_OFFSET_NONE;     /* 无偏移寄存器 */
    adc_conf_handler.OffsetRightShift       = ENABLE;              /* 右移防上溢（8和16）*/
    adc_conf_handler.OffsetSignedSaturation = DISABLE;             /* 按符号饱和（8和16，差分模式）*/
    HAL_ADC_ConfigChannel(&adc_init_handler, &adc_conf_handler);
}

void ADC_DMA_IRQHandler(void) {HAL_DMA_IRQHandler(&adc_dma_handler);}
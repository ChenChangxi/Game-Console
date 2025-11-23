#include "timer.h"

uint16_t ins;
uint16_t cnx;
uint16_t cny;
uint16_t time_stat;
uint16_t time_coun;
TIM_HandleTypeDef led_time_handler;
TIM_HandleTypeDef wdg_time_handler;
TIM_HandleTypeDef bln_time_handler;
TIM_HandleTypeDef kic_time_handler;
TIM_HandleTypeDef mst_time_handler;

void deay_time_init(uint16_t led_div, uint16_t led_cou, 
                    uint16_t wdg_div, uint16_t wdg_cou) {

    led_time_handler.Instance         = LED_TIME;
    led_time_handler.Init.Prescaler   = led_div;
    led_time_handler.Init.Period      = led_cou;
    led_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&led_time_handler);
    HAL_TIM_Base_Start_IT(&led_time_handler);

    wdg_time_handler.Instance         = WDG_TIME;
    wdg_time_handler.Init.Prescaler   = wdg_div;
    wdg_time_handler.Init.Period      = wdg_cou;
    wdg_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&wdg_time_handler);
    HAL_TIM_Base_Start_IT(&wdg_time_handler);
}

void mast_time_init(uint16_t div, uint16_t cou) {

    TIM_ClockConfigTypeDef  mst_clk_handler = {0};
    TIM_MasterConfigTypeDef mst_cfg_handler = {0};

    mst_time_handler.Instance         = MST_TIME;
    mst_time_handler.Init.Prescaler   = div;
    mst_time_handler.Init.Period      = cou;
    mst_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&mst_time_handler);

    mst_clk_handler.ClockFilter    = 0x0;                                /* 不滤波 */
    mst_clk_handler.ClockPolarity  = TIM_CLOCKPOLARITY_NONINVERTED;      /* 不反相 */
    mst_clk_handler.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;            /* 不分频 */
    mst_clk_handler.ClockSource    = TIM_CLOCKSOURCE_ETRMODE2;           /* 外部直连而非TRGI连ETRF */
    HAL_TIM_ConfigClockSource(&mst_time_handler, &mst_clk_handler);      /* 外部时钟模式2 */

    mst_cfg_handler.MasterOutputTrigger  = TIM_TRGO_UPDATE;              /* 定时器时钟源（更新触发）*/
    mst_cfg_handler.MasterSlaveMode      = TIM_MASTERSLAVEMODE_DISABLE;  /* 只作主不作从 */
    HAL_TIMEx_MasterConfigSynchronization(&mst_time_handler, &mst_cfg_handler);

    HAL_TIM_Base_Start(&mst_time_handler);
}

void comp_time_init(uint16_t div, uint16_t cou, uint16_t dea) {

    TIM_OC_InitTypeDef             bln_coc_handler = {0};
    TIM_BreakDeadTimeConfigTypeDef dea_brk_handler = {0};
    TIM_SlaveConfigTypeDef         bln_clk_handler = {0};

    bln_time_handler.Instance               = BLN_TIME;
    bln_time_handler.Init.Prescaler         = div;
    bln_time_handler.Init.Period            = cou;
    bln_time_handler.Init.CounterMode       = TIM_COUNTERMODE_UP;
    bln_time_handler.Init.RepetitionCounter = 10 - 1;                        /* N次溢出产生一次更新 */
    bln_time_handler.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV4;        /* 死区滤波采样时钟分频 */
    HAL_TIM_OC_Init(&bln_time_handler);

    bln_clk_handler.InputTrigger     = TIM_TS_ITR2;                          /* 时钟源为TIM3 */
    bln_clk_handler.SlaveMode        = TIM_SLAVEMODE_EXTERNAL1;              /* 外部时钟模式1 */
    HAL_TIM_SlaveConfigSynchro(&bln_time_handler, &bln_clk_handler);

    bln_coc_handler.OCMode       = TIM_OCMODE_PWM1;                          /* 输出模式 */
    bln_coc_handler.OCPolarity   = TIM_OCPOLARITY_HIGH;                      /* 有效电平 */
    bln_coc_handler.OCNPolarity  = TIM_OCNPOLARITY_LOW;                      /* 互补输出有效电平 */
    bln_coc_handler.OCIdleState  = TIM_OCIDLESTATE_RESET;                    /* 刹车断路后有效电平（OIS）*/
    bln_coc_handler.OCNIdleState = TIM_OCNIDLESTATE_RESET;                   /* 互补刹车断路后有效电平（OISN）*/
    HAL_TIM_OC_ConfigChannel(&bln_time_handler, &bln_coc_handler, BLN_TIME_PWM_CHANNEL);

    bln_coc_handler.OCMode     = TIM_OCMODE_TOGGLE;                          /* PHASE输出模式 */
    HAL_TIM_OC_ConfigChannel(&bln_time_handler, &bln_coc_handler, BLN_TIME_PHASEX_CHANNEL);

    bln_coc_handler.Pulse      = 500;                                        /* 初相为50% */
    bln_coc_handler.OCPolarity = TIM_OCPOLARITY_LOW;                         /* 异或后高电平有效 */
    HAL_TIM_OC_ConfigChannel(&bln_time_handler, &bln_coc_handler, BLN_TIME_PHASEY_CHANNEL);

    dea_brk_handler.LockLevel        = TIM_LOCKLEVEL_OFF;                    /* 关闭寄存器锁 */
    dea_brk_handler.DeadTime         = dea;                                  /* 死区时间 */
    dea_brk_handler.BreakState       = TIM_BREAK_ENABLE;                     /* 使能刹车断路 */
    dea_brk_handler.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;               /* 刹车断路极性 */
    dea_brk_handler.OffStateRunMode  = TIM_OSSR_ENABLE;                      /* 通道关闭后输出无效电平 */
    dea_brk_handler.OffStateIDLEMode = TIM_OSSI_ENABLE;                      /* 刹车断路后输出OIS和OISN电平 */
    dea_brk_handler.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;           /* 刹车断路后自动恢复 */
    HAL_TIMEx_ConfigBreakDeadTime(&bln_time_handler, &dea_brk_handler);

    __HAL_TIM_ENABLE_IT(&bln_time_handler, TIM_IT_UPDATE);                   /* 使能更新中断 */
    __HAL_TIM_ENABLE_OCxPRELOAD(&bln_time_handler, BLN_TIME_PWM_CHANNEL);    /* 使能通道预装载（PWM）*/
    __HAL_TIM_ENABLE_OCxPRELOAD(&bln_time_handler, BLN_TIME_PHASEX_CHANNEL); /* 使能通道预装载（PHASEX）*/
    __HAL_TIM_ENABLE_OCxPRELOAD(&bln_time_handler, BLN_TIME_PHASEY_CHANNEL); /* 使能通道预装载（PHASEY）*/
    HAL_TIM_OC_Start(&bln_time_handler, BLN_TIME_PWM_CHANNEL);               /* 使能输出（PWM）*/
    HAL_TIMEx_OCN_Start(&bln_time_handler, BLN_TIME_PWM_CHANNEL);            /* 使能互补输出（PWM）*/
    HAL_TIM_OC_Start_IT(&bln_time_handler, BLN_TIME_PHASEX_CHANNEL);         /* 使能输出和中断（PHASEX）*/
    HAL_TIM_OC_Start_IT(&bln_time_handler, BLN_TIME_PHASEY_CHANNEL);         /* 使能输出和中断（PHASEY）*/
}

void capt_time_init(uint16_t div, uint32_t cou) {

    TIM_IC_InitTypeDef kic_cap_handler = {0};

    kic_time_handler.Instance         = KIC_TIME;
    kic_time_handler.Init.Prescaler   = div;
    kic_time_handler.Init.Period      = cou;
    kic_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&kic_time_handler);

    kic_cap_handler.ICFilter    = 0x0;                         /* 采样滤波 */
    kic_cap_handler.ICPolarity  = TIM_ICPOLARITY_RISING;       /* 捕获边沿 */
    kic_cap_handler.ICPrescaler = TIM_ICPSC_DIV1;              /* 分频系数（N个边沿一次捕获）*/
    kic_cap_handler.ICSelection = TIM_ICSELECTION_INDIRECTTI;  /* 映射关系 */
    HAL_TIM_IC_ConfigChannel(&kic_time_handler, &kic_cap_handler, KIC_TIME_CHANNEL);

    __HAL_TIM_ENABLE_IT(&kic_time_handler, TIM_IT_UPDATE);     /* 启动更新中断 */
    HAL_TIM_IC_Start_IT(&kic_time_handler, KIC_TIME_CHANNEL);  /* 启动计数器和捕获中断且使能输入 */
}

uint16_t get_pers(uint16_t per, uint16_t *cou) {
    
    return (uint16_t)(per - abs(per - ((*cou)++ % (per * 2))));
}

uint16_t get_digs(uint32_t time_tota) {
    
    uint8_t size = 0;do {size++;time_tota /= 10;} while (time_tota > 0);return size;
}

void LED_BLN_UP_IRQHandler(void) {
    
    HAL_TIM_IRQHandler(&led_time_handler);HAL_TIM_IRQHandler(&bln_time_handler);
}

void LED_DAC_IRQHandler(void) {HAL_TIM_IRQHandler(&led_time_handler);}

void WDG_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&wdg_time_handler);}

void BLN_TIME_UP_IRQHandler(void) {HAL_TIM_IRQHandler(&bln_time_handler);}

void BLN_TIME_CC_IRQHandler(void) {HAL_TIM_IRQHandler(&bln_time_handler);}

void KIC_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&kic_time_handler);}
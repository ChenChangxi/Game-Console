#include "timer.h"

uint16_t                ins;
uint16_t                cnt;
uint16_t                time_stat;
uint16_t                time_coun;
uint32_t                time_tota;
uint8_t                 time_data[KIC_TIME_DATA_SIZE];
TIM_HandleTypeDef       led_time_handler;
TIM_HandleTypeDef       wdg_time_handler;
TIM_HandleTypeDef       bln_time_handler;
TIM_HandleTypeDef       kic_time_handler;
TIM_HandleTypeDef       mst_time_handler;
GPIO_InitTypeDef        bln_gpio_handler;
GPIO_InitTypeDef        kic_gpio_handler;
GPIO_InitTypeDef        mst_gpio_handler;
TIM_OC_InitTypeDef      bln_pwm_handler;
TIM_IC_InitTypeDef      kic_cap_handler;
TIM_SlaveConfigTypeDef  bln_clk_handler;
TIM_ClockConfigTypeDef  mst_clk_handler;
TIM_MasterConfigTypeDef mst_cfg_handler;

void deay_time_init(uint16_t led_div, uint16_t led_cou, 
                    uint16_t wdg_div, uint16_t wdg_cou) {

    led_time_handler.Instance         = LED_TIME;
    led_time_handler.Init.Prescaler   = led_div;
    led_time_handler.Init.Period      = led_cou;
    led_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;    /* 递增计数 */
    HAL_TIM_Base_Init(&led_time_handler);
    HAL_TIM_Base_Start_IT(&led_time_handler);

    wdg_time_handler.Instance         = WDG_TIME;
    wdg_time_handler.Init.Prescaler   = wdg_div;
    wdg_time_handler.Init.Period      = wdg_cou;
    wdg_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&wdg_time_handler);
    HAL_TIM_Base_Start_IT(&wdg_time_handler);
}

void LED_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&led_time_handler);}

void WDG_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&wdg_time_handler);}

uint16_t get_pers(uint16_t per) {return (uint16_t)(per - abs(per - (ins++ % (per * 2))));}

void comp_time_init(uint16_t div, uint16_t cou) {

    bln_time_handler.Instance         = BLN_TIME;
    bln_time_handler.Init.Prescaler   = div;
    bln_time_handler.Init.Period      = cou;
    bln_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_PWM_Init(&bln_time_handler);

    bln_pwm_handler.OCMode     = TIM_OCMODE_PWM1;                       /* PWM1输出模式 */
    bln_pwm_handler.OCPolarity = TIM_OCPOLARITY_HIGH;                   /* 高电平有效 */
    bln_pwm_handler.Pulse      = cou / 2;                               /* 输出比较值（占空比）*/
    HAL_TIM_PWM_ConfigChannel(&bln_time_handler, &bln_pwm_handler, BLN_TIME_CHANNEL);

    bln_clk_handler.InputTrigger     = TIM_TS_ITR2;                     /* 时钟源为TIM3 */
    bln_clk_handler.SlaveMode        = TIM_SLAVEMODE_EXTERNAL1;         /* 外部时钟模式1 */
    HAL_TIM_SlaveConfigSynchro(&bln_time_handler, &bln_clk_handler);

    __HAL_TIM_ENABLE_OCxPRELOAD(&bln_time_handler, BLN_TIME_CHANNEL);   /* 使能通道预装载 */
    HAL_TIM_PWM_Start(&bln_time_handler, BLN_TIME_CHANNEL);             /* 启动计数器且使能输出 */ 
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BLN_TIME) {

        BLN_GPIO_CLK_ENABLE();
        BLN_TIME_CLK_ENABLE();

        bln_gpio_handler.Pin       = BLN_TIME_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        bln_gpio_handler.Alternate = BLN_TIME_AF;
        bln_gpio_handler.Pull      = GPIO_PULLDOWN;
        bln_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);
    }
}

uint8_t get_digs(uint32_t time_tota) {
    
    uint8_t size = 0;do {size++;time_tota /= 10;} while (time_tota > 0);return size;
}

void capt_time_init(uint16_t div, uint16_t cou) {

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

    __HAL_TIM_ENABLE_IT(&kic_time_handler, TIM_IT_UPDATE);     /* 启动更新中断*/
    HAL_TIM_IC_Start_IT(&kic_time_handler, KIC_TIME_CHANNEL);  /* 启动计数器和捕获中断且使能输入 */
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == KIC_TIME) {
        
        KIC_GPIO_CLK_ENABLE();
        KIC_TIME_CLK_ENABLE();

        kic_gpio_handler.Pin       = KIC_TIME_PIN;
        kic_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        kic_gpio_handler.Alternate = KIC_TIME_AF;
        kic_gpio_handler.Pull      = GPIO_PULLDOWN;
        kic_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(KIC_TIME_PORT, &kic_gpio_handler);
        HAL_NVIC_EnableIRQ(KIC_TIME_IRQn);
        HAL_NVIC_SetPriority(KIC_TIME_IRQn, 3, 2);
    }
}

void KIC_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&kic_time_handler);}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == KIC_TIME) {

        if (!(time_stat & 0x8000)) {

            if (!(time_stat & 0x4000)) {                      /* 来了上升沿 */

                time_stat |= 0x4000;
                __HAL_TIM_DISABLE(&kic_time_handler);         /* 关闭定时器 */
                __HAL_TIM_SET_COUNTER(&kic_time_handler, 0);  /* 计数器清零 */
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除上升沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_FALLING);   /* 改为下降沿触发 */
                __HAL_TIM_ENABLE(&kic_time_handler);          /* 打开定时器 */

            } else {                                          /* 来了下降沿 */

                time_stat |= 0x8000;
                time_coun = HAL_TIM_ReadCapturedValue(&kic_time_handler, KIC_TIME_CHANNEL);             /* 读取计数器的值 */
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除下降沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_RISING);    /* 改为上升沿触发 */
            }
        }
    }
}

void mast_time_init(uint16_t div, uint16_t cou) {

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

    HAL_TIM_Base_Start_IT(&mst_time_handler);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == LED_TIME) {

        LED_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(LED_TIME_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(LED_TIME_IRQn);

    } else if (htim->Instance == WDG_TIME) {

        WDG_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(WDG_TIME_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(WDG_TIME_IRQn);

    } else if (htim->Instance == MST_TIME) {

        MST_GPIO_CLK_ENABLE();
        MST_TIME_CLK_ENABLE();

        mst_gpio_handler.Pin       = MST_TIME_PIN;
        mst_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        mst_gpio_handler.Alternate = MST_TIME_AF;
        mst_gpio_handler.Pull      = GPIO_PULLDOWN;
        mst_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MST_TIME_PORT, &mst_gpio_handler);
        HAL_NVIC_EnableIRQ(MST_TIME_IRQn);
        HAL_NVIC_SetPriority(MST_TIME_IRQn, 3, 1);
    }
}

void MST_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&mst_time_handler);}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == LED_TIME) {LED0_TOGGLE();LED1_TOGGLE();}
    else if (htim->Instance == WDG_TIME) {iwdg_feed();wwdg_feed();}
    else if (htim->Instance == KIC_TIME) {

        if (!(time_stat & 0x8000) && (time_stat & 0x4000)) {  /* 未准备发送且来了上升沿 */

            if ((time_stat & 0x3fff) != 0x3fff) time_stat++;  /* 周期数达到最大值 */
            else {

                time_stat |= 0x8000;
                time_coun = 0xffff;
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除下降沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_RISING);    /* 改为上升沿触发 */
            }
        }
    } else if (htim->Instance == MST_TIME) {

        if (++cnt == 10000) {__HAL_TIM_SET_COMPARE(&bln_time_handler, BLN_TIME_CHANNEL, get_pers(400));cnt = 0;}
    }
}
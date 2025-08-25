#include "timer.h"

uint16_t           ins;
TIM_HandleTypeDef  led_time_handler;
TIM_HandleTypeDef  wdg_time_handler;
TIM_HandleTypeDef  bln_time_handler;
GPIO_InitTypeDef   bln_gpio_handler;
TIM_OC_InitTypeDef bln_pwm_handler;

void base_time_init(uint16_t led_div, uint16_t led_cou, 
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

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == LED_TIME) {

        LED_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(LED_TIME_IRQn, 2, 1);
        HAL_NVIC_EnableIRQ(LED_TIME_IRQn);

    } else if (htim->Instance == WDG_TIME) {

        WDG_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(WDG_TIME_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(WDG_TIME_IRQn);
    }
}

void LED_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&led_time_handler);}

void WDG_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&wdg_time_handler);}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    
    if (htim->Instance == LED_TIME) {LED0_TOGGLE();LED1_TOGGLE();}
    else if (htim->Instance == WDG_TIME) {iwdg_feed();wwdg_feed();}
}

uint16_t get_pers(void) {return (uint16_t)(400 - abs(400 - (ins++ % 800)));}

void gene_time_init(uint16_t div, uint16_t cou) {

    bln_time_handler.Instance         = BLN_TIME;
    bln_time_handler.Init.Prescaler   = div;
    bln_time_handler.Init.Period      = cou;
    bln_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;    /* 递增计数 */
    HAL_TIM_PWM_Init(&bln_time_handler);

    bln_pwm_handler.OCMode     = TIM_OCMODE_PWM1;              /* PWM1输出模式 */
    bln_pwm_handler.OCPolarity = TIM_OCPOLARITY_HIGH;          /* 高电平有效 */
    bln_pwm_handler.Pulse      = cou / 2;                      /* 输出比较值（占空比）*/
    HAL_TIM_PWM_ConfigChannel(&bln_time_handler, &bln_pwm_handler, BLN_TIME_CHANNEL);

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
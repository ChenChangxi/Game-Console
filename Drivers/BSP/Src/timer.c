#include "timer.h"

uint16_t           ins;
TIM_HandleTypeDef  base_time_handler;
TIM_HandleTypeDef  gene_time_handler;
GPIO_InitTypeDef   gene_gpio_handler;
TIM_OC_InitTypeDef gene_pwm_handler;

void base_time_init(uint16_t div, uint16_t cou) {

    base_time_handler.Instance       = BASE_TIME;
    base_time_handler.Init.Prescaler = div;
    base_time_handler.Init.Period    = cou;
    HAL_TIM_Base_Init(&base_time_handler);
    HAL_TIM_Base_Start_IT(&base_time_handler);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BASE_TIME) {

        BASE_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(BASE_TIME_IRQn, 1, 3);
        HAL_NVIC_EnableIRQ(BASE_TIME_IRQn);
    }
}

void BASE_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&base_time_handler);}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    
    if (htim->Instance == BASE_TIME) {LED0_TOGGLE();LED1_TOGGLE();}
}

uint16_t get_pers(void) {return (uint16_t)(400 - abs(400 - (ins++ % 800)));}

void gene_time_init(uint16_t div, uint16_t cou) {

    gene_time_handler.Instance         = GENE_TIME_PWM;
    gene_time_handler.Init.Prescaler   = div;
    gene_time_handler.Init.Period      = cou;
    gene_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;    /* 递增计数 */
    HAL_TIM_PWM_Init(&gene_time_handler);

    gene_pwm_handler.OCMode     = TIM_OCMODE_PWM1;              /* PWM1输出模式 */
    gene_pwm_handler.OCPolarity = TIM_OCPOLARITY_HIGH;          /* 高电平有效 */
    gene_pwm_handler.Pulse      = cou / 2;                      /* 输出比较值（占空比）*/
    HAL_TIM_PWM_ConfigChannel(&gene_time_handler, &gene_pwm_handler, GENE_TIME_PWM_CHANNEL);

    __HAL_TIM_ENABLE_OCxPRELOAD(&gene_time_handler, GENE_TIME_PWM_CHANNEL);   /* 使能通道预装载 */
    HAL_TIM_PWM_Start(&gene_time_handler, GENE_TIME_PWM_CHANNEL);             /* 启动计数器且使能输出 */ 
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == GENE_TIME_PWM) {

        GENE_GPIO_PWM_ENABLE();
        GENE_TIME_PWM_ENABLE();

        gene_gpio_handler.Pin       = GENE_TIME_PWM_PIN;
        gene_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        gene_gpio_handler.Alternate = GENE_TIME_PWM_AF;
        gene_gpio_handler.Pull      = GPIO_PULLDOWN;
        gene_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GENE_TIME_PWM_PORT, &gene_gpio_handler);
    }
}
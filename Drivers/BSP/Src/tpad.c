#include "tpad.h"

uint16_t          ctor_coun;
TIM_HandleTypeDef tpad_time_handler;

void tpad_init(uint16_t div) {

    TIM_IC_InitTypeDef tpad_cap_handler = {0};

    tpad_time_handler.Instance         = TPAD_TIME;
    tpad_time_handler.Init.Prescaler   = div;
    tpad_time_handler.Init.Period      = 0xffffffff - 1;
    tpad_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&tpad_time_handler);

    tpad_cap_handler.ICFilter    = 0x0;
    tpad_cap_handler.ICPolarity  = TIM_ICPOLARITY_RISING;
    tpad_cap_handler.ICPrescaler = TIM_ICPSC_DIV1;
    tpad_cap_handler.ICSelection = TIM_ICSELECTION_DIRECTTI;
    HAL_TIM_IC_ConfigChannel(&tpad_time_handler, &tpad_cap_handler, TPAD_TIME_CHANNEL);
    LL_GPIO_SetPinMode(TPAD_GPIO_PORT, TPAD_GPIO_PIN, GPIO_MODE_OUTPUT_PP);   /* 电容放电 */
    LL_GPIO_SetPinMode(TPAD_GPIO_PORT, TPAD_GPIO_PIN, GPIO_MODE_AF_PP);       /* 电容充电 */
    HAL_TIM_IC_Start_IT(&tpad_time_handler, TPAD_TIME_CHANNEL);
}

void TPAD_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&tpad_time_handler);}
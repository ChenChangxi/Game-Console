#include "timer.h"

TIM_HandleTypeDef base_time_handler;

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
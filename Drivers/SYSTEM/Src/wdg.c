#include "wdg.h"

uint8_t feed_iwdg[]  = "请喂iwdg\r\n";
uint8_t feed_wwdg[]  = "请喂wwdg\r\n";
uint8_t iwdg_reset[] = "iwdg复位\r\n";
uint8_t wwdg_reset[] = "wwdg复位\r\n";
uint8_t exte_reset[] = "外部复位\r\n";
uint8_t stat_reset[] = "上电复位\r\n";
IWDG_HandleTypeDef iwdg_handler;
WWDG_HandleTypeDef wwdg_handler;
TIM_HandleTypeDef  wwdg_time_handler;

void iwdg_init(uint8_t div, uint16_t load) {

    iwdg_handler.Instance       = IWDG;
    iwdg_handler.Init.Prescaler = div;
    iwdg_handler.Init.Reload    = load;
    iwdg_handler.Init.Window    = IWDG_WINDOW_DISABLE;   /* H743的IWDG有窗口模式 */
    HAL_IWDG_Init(&iwdg_handler);
}

void wwdg_init(uint32_t div, uint8_t cou, uint8_t win, uint16_t tdv, uint16_t tco) {

    wwdg_handler.Instance       = WWDG;
    wwdg_handler.Init.Prescaler = div;
    wwdg_handler.Init.Counter   = cou;
    wwdg_handler.Init.Window    = win;
    wwdg_handler.Init.EWIMode   = WWDG_EWI_ENABLE;       /* 唤醒中断 */
    HAL_WWDG_Init(&wwdg_handler);

    wwdg_time_handler.Instance         = WWDG_TIME;
    wwdg_time_handler.Init.Prescaler   = tdv;
    wwdg_time_handler.Init.Period      = tco;
    wwdg_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&wwdg_time_handler);
    HAL_TIM_Base_Start_IT(&wwdg_time_handler);
}

void iwdg_feed(void) {HAL_IWDG_Refresh(&iwdg_handler);}

void wwdg_feed(void) {HAL_WWDG_Refresh(&wwdg_handler);}

void WWDG_IRQHandler(void) {HAL_WWDG_IRQHandler(&wwdg_handler);}

void WWDG_TIME_IRQHandler(void) {HAL_TIM_IRQHandler(&wwdg_time_handler);}
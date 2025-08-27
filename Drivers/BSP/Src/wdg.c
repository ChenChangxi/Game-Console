#include "wdg.h"

IWDG_HandleTypeDef iwdg_handler;
WWDG_HandleTypeDef wwdg_handler;
uint8_t feed_iwdg[]  = "请喂iwdg\r\n";
uint8_t feed_wwdg[]  = "请喂wwdg\r\n";
uint8_t iwdg_reset[] = "iwdg复位\r\n";
uint8_t wwdg_reset[] = "wwdg复位\r\n";
uint8_t exte_reset[] = "外部复位\r\n";
uint8_t stat_reset[] = "上电复位\r\n";

void iwdg_init(uint8_t div, uint16_t load) {

    iwdg_handler.Instance       = IWDG1;
    iwdg_handler.Init.Prescaler = div;
    iwdg_handler.Init.Reload    = load;
    iwdg_handler.Init.Window    = IWDG_WINDOW_DISABLE;   /* H743的IWDG有窗口模式 */
    HAL_IWDG_Init(&iwdg_handler);
}

void iwdg_feed(void) {HAL_IWDG_Refresh(&iwdg_handler);}

void wwdg_init(uint8_t div, uint8_t cou, uint8_t win) {

    wwdg_handler.Instance       = WWDG1;
    wwdg_handler.Init.Prescaler = div;
    wwdg_handler.Init.Counter   = cou;
    wwdg_handler.Init.Window    = win;
    wwdg_handler.Init.EWIMode   = WWDG_EWI_ENABLE;       /* 唤醒中断 */
    HAL_WWDG_Init(&wwdg_handler);
}

void wwdg_feed(void) {HAL_WWDG_Refresh(&wwdg_handler);}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg) {

    __HAL_RCC_WWDG_CLK_ENABLE();
    HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void) {HAL_WWDG_IRQHandler(&wwdg_handler);}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg) {wwdg_feed();}
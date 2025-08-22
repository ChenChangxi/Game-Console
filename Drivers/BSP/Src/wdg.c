#include "wdg.h"

IWDG_HandleTypeDef iwdg_handler;
WWDG_HandleTypeDef wwdg_handler;
uint8_t feed_iwdg[WDG_LEN]  = 
    {0xE8, 0xAF, 0xB7, 0xE5, 0x96, 0x82, 0x69, 0x77, 0x64, 0x67, 0x0D, 0x0A};
uint8_t feed_wwdg[WDG_LEN]  = 
    {0xE8, 0xAF, 0xB7, 0xE5, 0x96, 0x82, 0x77, 0x77, 0x64, 0x67, 0x0D, 0x0A};
uint8_t iwdg_reset[WDG_LEN] = 
    {0x69, 0x77, 0x64, 0x67, 0xE5, 0xA4, 0x8D, 0xE4, 0xBD, 0x8D, 0x0D, 0x0A};
uint8_t wwdg_reset[WDG_LEN] = 
    {0x77, 0x77, 0x64, 0x67, 0xE5, 0xA4, 0x8D, 0xE4, 0xBD, 0x8D, 0x0D, 0x0A};
uint8_t exte_reset[WDG_LEN] = 
    {0xE5, 0xA4, 0x96, 0xE9, 0x83, 0xA8, 0xE5, 0xA4, 0x8D, 0xE4, 0xBD, 0x8D, 0x0D, 0x0A};
uint8_t stat_reset[WDG_LEN] = 
    {0xE4, 0xB8, 0x8A, 0xE7, 0x94, 0xB5, 0xE5, 0xA4, 0x8D, 0xE4, 0xBD, 0x8D, 0x0D, 0x0A};

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
    HAL_NVIC_SetPriority(WWDG_IRQn, 3, 2);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void) {HAL_WWDG_IRQHandler(&wwdg_handler);}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg) {wwdg_feed();}
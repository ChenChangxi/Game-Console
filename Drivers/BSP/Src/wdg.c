#include "wdg.h"

IWDG_HandleTypeDef iwdg_handler;
uint8_t ask[IWDG_FEED]  = {0xE8, 0xAF, 0xB7, 0xE5, 0x96, 0x82, 0xE7, 0x8B, 0x97, 0x0D, 0x0A};
uint8_t done[IWDG_FEED] = {0xE5, 0xB7, 0xB2, 0xE5, 0x96, 0x82, 0xE7, 0x8B, 0x97, 0x0D, 0x0A};

void iwdg_init(uint8_t div, uint16_t load) {

    iwdg_handler.Instance       = IWDG;
    iwdg_handler.Init.Prescaler = div;
    iwdg_handler.Init.Reload    = load;
    HAL_IWDG_Init(&iwdg_handler);
}

void iwdg_feed(void) {HAL_IWDG_Refresh(&iwdg_handler);}
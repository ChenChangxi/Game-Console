#include "key.h"
#include "lcd.h"
#include "tpad.h"
#include "timer.h"
#include "usart.h"
#include "sdram.h"

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART) {

        GPIO_InitTypeDef gpio_handler = {0};

        USART_CLK_ENABLE();
        USART_GPIO_CLK_ENABLE();

        gpio_handler.Pin       = USART_GPIO_PIN;
        gpio_handler.Mode      = GPIO_MODE_AF_PP;
        gpio_handler.Alternate = USART_GPIO_AF;
        gpio_handler.Pull      = GPIO_PULLUP;
        gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(USART_GPIO_PORT, &gpio_handler);

#if USART_EN_RX
        HAL_NVIC_SetPriority(USART_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART_IRQn);
#endif
    }
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg) {

    if (hwwdg->Instance == WWDG) {

        WWDG_CLK_ENABLE();
        HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(WWDG_IRQn);
    }
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

        GPIO_InitTypeDef mst_gpio_handler = {0};

        MST_GPIO_CLK_ENABLE();
        MST_TIME_CLK_ENABLE();

        mst_gpio_handler.Pin       = MST_TIME_PIN;
        mst_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        mst_gpio_handler.Alternate = MST_TIME_AF;
        mst_gpio_handler.Pull      = GPIO_PULLDOWN;
        mst_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MST_TIME_PORT, &mst_gpio_handler);
    }
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BLN_TIME) {

        GPIO_InitTypeDef bln_gpio_handler = {0};

        BLN_GPIO_CLK_ENABLE();
        BLC_GPIO_CLK_ENABLE();
        BLB_GPIO_CLK_ENABLE();
        BLN_TIME_CLK_ENABLE();

        bln_gpio_handler.Pin       = BLN_TIME_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        bln_gpio_handler.Alternate = BLN_TIME_AF;
        bln_gpio_handler.Pull      = GPIO_PULLDOWN;
        bln_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLC_TIME_PIN;
        HAL_GPIO_Init(BLC_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLB_TIME_PIN;
        HAL_GPIO_Init(BLB_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLN_TIME_PHASE_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_OUTPUT_PP;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);

        HAL_NVIC_EnableIRQ(BLN_TIME_UP_IRQn);
        HAL_NVIC_EnableIRQ(BLN_TIME_CC_IRQn);
        HAL_NVIC_SetPriority(BLN_TIME_UP_IRQn, 3, 1);
        HAL_NVIC_SetPriority(BLN_TIME_CC_IRQn, 3, 1);
    }
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == KIC_TIME) {

        GPIO_InitTypeDef kic_gpio_handler = {0};

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

    } else if (htim->Instance == TPAD_TIME) {

        GPIO_InitTypeDef tpad_gpio_handler = {0};

        TPAD_GPIO_CLK_ENABLE();
        TPAD_TIME_CLK_ENABLE();

        tpad_gpio_handler.Pin       = TPAD_GPIO_PIN;
        tpad_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        tpad_gpio_handler.Alternate = TPAD_GPIO_AF;
        tpad_gpio_handler.Pull      = GPIO_NOPULL;
        tpad_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(TPAD_GPIO_PORT, &tpad_gpio_handler);
        HAL_NVIC_EnableIRQ(TPAD_TIME_IRQn);
        HAL_NVIC_SetPriority(TPAD_TIME_IRQn, 3, 3);
    }
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram) {

    GPIO_InitTypeDef lcd_gpio_handler = {0};

    LCD_CON_CLK_ENABLE();
    LCD_BLN_CLK_ENABLE();

    lcd_gpio_handler.Pin       = LCD_CON_PIN;
    lcd_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    lcd_gpio_handler.Alternate = LCD_AF;
    lcd_gpio_handler.Pull      = GPIO_PULLUP;
    lcd_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_CON_PORT, &lcd_gpio_handler);

    lcd_gpio_handler.Pin       = LCD_BLN_PIN;
    lcd_gpio_handler.Mode      = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_BLN_PORT, &lcd_gpio_handler);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram) {

    GPIO_InitTypeDef sdram_gpio_handler = {0};

    SDRAM_CAS_CLK_ENABLE();
    SDRAM_RAS_CLK_ENABLE();
    SDRAM_WER_CLK_ENABLE();
    SDRAM_CSE_CLK_ENABLE();
    SDRAM_BAN_CLK_ENABLE();
    SDRAM_CLK_CLK_ENABLE();
    SDRAM_CKE_CLK_ENABLE();
    SDRAM_NBL_CLK_ENABLE();

    sdram_gpio_handler.Pin       = SDRAM_CAS_PIN;
    sdram_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    sdram_gpio_handler.Alternate = SDRAM_AF;
    sdram_gpio_handler.Pull      = GPIO_PULLUP;
    sdram_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDRAM_CAS_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_RAS_PIN;
    HAL_GPIO_Init(SDRAM_RAS_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_WER_PIN;
    HAL_GPIO_Init(SDRAM_WER_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CSE_PIN;
    HAL_GPIO_Init(SDRAM_CSE_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_BAN_PIN;
    HAL_GPIO_Init(SDRAM_BAN_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CLK_PIN;
    HAL_GPIO_Init(SDRAM_CLK_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CKE_PIN;
    HAL_GPIO_Init(SDRAM_CKE_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_NBL_PIN;
    HAL_GPIO_Init(SDRAM_NBL_PORT, &sdram_gpio_handler);
}
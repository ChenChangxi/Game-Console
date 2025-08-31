#include "key.h"
#include "timer.h"
#include "usart.h"

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART_UX) {

        GPIO_InitTypeDef gpio_handler = {0};

        USART_UX_CLK_ENABLE();
        USART_TX_GPIO_CLK_ENABLE();
        USART_RX_GPIO_CLK_ENABLE();

        gpio_handler.Pin       = USART_TX_GPIO_PIN;
        gpio_handler.Mode      = GPIO_MODE_AF_PP;
        gpio_handler.Alternate = USART_TX_GPIO_AF;
        gpio_handler.Pull      = GPIO_PULLUP;
        gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_handler);

        gpio_handler.Pin       = USART_RX_GPIO_PIN;
        gpio_handler.Alternate = USART_RX_GPIO_AF;
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_handler);

#if USART_UX_EN_RX
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);
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

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BLN_TIME) {

        GPIO_InitTypeDef bln_gpio_handler = {0};

        BLN_GPIO_CLK_ENABLE();
        BLN_TIME_CLK_ENABLE();

        bln_gpio_handler.Pin       = BLN_TIME_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        bln_gpio_handler.Alternate = BLN_TIME_AF;
        bln_gpio_handler.Pull      = GPIO_PULLDOWN;
        bln_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);
        HAL_NVIC_EnableIRQ(BLN_TIME_IRQn);
        HAL_NVIC_SetPriority(BLN_TIME_IRQn, 3, 1);
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
    }
}
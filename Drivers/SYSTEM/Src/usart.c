#include "usart.h"

UART_HandleTypeDef uart_handler;
#if USART_UX_EN_RX
uint16_t           stat;
uint8_t            buff[USART_UX_BUFF_SIZE];
#endif
uint8_t            data[USART_UX_DATA_SIZE];

void usart_init(uint32_t baud) {

    uart_handler.Instance            = USART_UX;
    uart_handler.Init.BaudRate       = baud;
    uart_handler.Init.WordLength     = UART_WORDLENGTH_8B;
    uart_handler.Init.StopBits       = UART_STOPBITS_1;
    uart_handler.Init.Mode           = UART_MODE_TX_RX;
    uart_handler.Init.OverSampling   = UART_OVERSAMPLING_16;          /* 过采样 */
    uart_handler.Init.Parity         = UART_PARITY_NONE;              /* 奇偶校验 */
    uart_handler.Init.HwFlowCtl      = UART_HWCONTROL_NONE;           /* 硬件流控 */
    uart_handler.Init.ClockPrescaler = UART_PRESCALER_DIV1;           /* USART核时钟分频系数 */
    uart_handler.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;   /* 一次采样 */
    HAL_UART_Init(&uart_handler);
    HAL_UART_Receive_IT(&uart_handler, buff, USART_UX_BUFF_SIZE);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

    GPIO_InitTypeDef rtx_init;

    if (huart->Instance == USART_UX) {

        USART_UX_CLK_ENABLE();
        USART_TX_GPIO_CLK_ENABLE();
        USART_RX_GPIO_CLK_ENABLE();

        rtx_init.Pin       = USART_TX_GPIO_PIN;
        rtx_init.Mode      = GPIO_MODE_AF_PP;
        rtx_init.Alternate = USART_TX_GPIO_AF;
        rtx_init.Pull      = GPIO_PULLUP;
        rtx_init.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &rtx_init);

        rtx_init.Pin       = USART_RX_GPIO_PIN;
        rtx_init.Alternate = USART_RX_GPIO_AF;
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &rtx_init);

#if USART_UX_EN_RX
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);
#endif
    }
}

void usart_transmit(uint8_t *tran, uint16_t size) {

    HAL_UART_Transmit(&uart_handler, tran, size, 1000);
    while (__HAL_UART_GET_FLAG(&uart_handler, UART_FLAG_TC) != SET);
}

void USART_UX_IRQHandler(void) {

    HAL_UART_IRQHandler(&uart_handler);
    HAL_UART_Receive_IT(&uart_handler, buff, USART_UX_BUFF_SIZE);   /* 防止被清中断 */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART_UX) {

        if (!(stat & 0x8000)) {

            if (stat & 0x4000) {if (buff[0] == 0x0a) stat |= 0x8000;else stat = 0;}      /* 收到了\n */
            else {

                if (buff[0] == 0x0d) stat |= 0x4000;                                     /* 收到了\r */
                else {data[stat++] = buff[0];if (stat >= USART_UX_DATA_SIZE) stat = 0;}
            }
        }
    }
}
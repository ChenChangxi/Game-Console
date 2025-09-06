#include "usart.h"

UART_HandleTypeDef uart_handler;
#if USART_EN_RX
uint16_t           uart_stat;
uint8_t            buff;
#endif
uint8_t            data[USART_DATA_SIZE];

void usart_init(uint32_t baud) {

    uart_handler.Instance            = USART;
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
    HAL_UART_Receive_IT(&uart_handler, &buff, USART_BUFF_SIZE);
}

void usart_transmit(uint8_t *tran, uint16_t size) {

    HAL_UART_Transmit(&uart_handler, tran, size, 1000);
    while (__HAL_UART_GET_FLAG(&uart_handler, UART_FLAG_TC) != SET);
}

void USART_IRQHandler(void) {

    HAL_UART_IRQHandler(&uart_handler);
    HAL_UART_Receive_IT(&uart_handler, &buff, USART_BUFF_SIZE);       /* 防止被清中断 */
}
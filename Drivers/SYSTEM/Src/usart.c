#include "usart.h"

UART_HandleTypeDef uart_handler;
DMA_HandleTypeDef  uart_dma_handler;
uint16_t           uart_stat;
uint8_t            buff;
uint8_t            data[USART_DATA_SIZE];
uint8_t            uart_dma_state;

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

    sys_cache_sram_sync((uint32_t)tran, (uint32_t)size);  /* 将DCache刷回SRAM */
    HAL_UART_Transmit_DMA(&uart_handler, tran, size);     /* 发送DMA请求 */
    while (!uart_dma_state && size);uart_dma_state = 0;   /* size为0时不会发起DMA传输 */
}

void USART_IRQHandler(void) {

    HAL_UART_IRQHandler(&uart_handler);
    HAL_UART_Receive_IT(&uart_handler, &buff, USART_BUFF_SIZE);   /* 防止被清中断 */
}

void USART_DMA_IRQHandler(void) {HAL_DMA_IRQHandler(&uart_dma_handler);}
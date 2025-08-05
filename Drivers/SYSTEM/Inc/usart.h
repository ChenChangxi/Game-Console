/* RS232串口 */

#ifndef __USART_H
#define __USART_H

#include "sys.h"

/* TX和RX的引脚 */
#define USART_TX_GPIO_PORT           GPIOB
#define USART_TX_GPIO_PIN            GPIO_PIN_10
#define USART_TX_GPIO_AF             GPIO_AF7_USART3   /* IO引脚复用器 */
#define USART_TX_GPIO_CLK_ENABLE()   do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

#define USART_RX_GPIO_PORT           GPIOB
#define USART_RX_GPIO_PIN            GPIO_PIN_11
#define USART_RX_GPIO_AF             GPIO_AF7_USART3
#define USART_RX_GPIO_CLK_ENABLE()   do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

/* USART */
#define USART_UX                     USART3
#define USART_UX_IRQn                USART3_IRQn
#define USART_UX_IRQHandler          USART3_IRQHandler
#define USART_UX_CLK_ENABLE()        do {__HAL_RCC_USART3_CLK_ENABLE();} while(0)
#define USART_UX_EN_RX               1                 /* 条件编译是否允许读中断 */
#define USART_UX_BUFF_SIZE           1                 /* 缓冲区大小 */
#define USART_UX_DATA_SIZE           200               /* 数据区大小 */
#define USART_UX_EXTI_SIZE           13                /* EXTI发送字符串大小 */

/* 条件编译是否定义 */
extern UART_HandleTypeDef uart_handler;                /* UART句柄 */
extern uint16_t           stat;                        /* 0~1为\n~\r，2~15为数据区大小，最大为16K */
extern uint8_t            buff[USART_UX_BUFF_SIZE];    /* 收发缓冲区（字节为单位）*/
extern uint8_t            data[USART_UX_DATA_SIZE];    /* 收发数据区（字节为单位）*/
extern uint8_t            exti[USART_UX_EXTI_SIZE];    /* EXTI发送字符串 */

/* USART初始化 */
void usart_init(uint32_t baud);

/* USART发送数据 */
void usart_transmit(uint8_t *tran, uint16_t size);

#endif
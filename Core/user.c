#include "key.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(336, 8, 2, 7);
    delay_init(168);
    led_init();
    key_init();
    beep_init();
    usart_init(115200);

    while (1) {

        LED0(0);LED1(1);BEEP(0);delay_ms(500);
        LED0(1);LED1(0);BEEP(0);delay_ms(500);
        if (stat & 0x8000) {

            HAL_UART_Transmit(&uart_handler, data, stat & 0x3fff, 1000);       /* 低14位为长度 */
            while (__HAL_UART_GET_FLAG(&uart_handler, UART_FLAG_TC) != SET);   /* 等待发送完成 */
            stat = 0;
        }
    }
}
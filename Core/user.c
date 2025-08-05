#include "key.h"
#include "wdg.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(336, 8, 2, 7);
    delay_init(168);
    led_init();
    key_init();
    beep_init();
    usart_init(115200);
    usart_transmit(ask, IWDG_FEED);
    iwdg_init(IWDG_PRESCALER_8, 4000);

    while (1) {

        LED0(0);LED1(1);BEEP(0);delay_ms(502);
        LED0(1);LED1(0);BEEP(0);delay_ms(500);
        iwdg_feed();usart_transmit(done, IWDG_FEED);
        if (stat & 0x8000) {usart_transmit(data, stat & 0x3fff);stat = 0;}   /* 低14位为长度 */
    }
}
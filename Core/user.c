#include "delay.h"
#include "led.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(336, 8, 2, 7);
    delay_init(168);
    led_init();

    while (1) {

        LED0(0);
        LED1(1);
        delay_ms(500);
        LED0(1);
        LED1(0);
        delay_ms(500);
    }
}
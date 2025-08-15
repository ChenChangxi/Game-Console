#include "led.h"

GPIO_InitTypeDef led_handler;

void led_init(void) {

    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();

    led_handler.Pin   = LED0_GPIO_PIN;
    led_handler.Mode  = GPIO_MODE_OUTPUT_PP;
    led_handler.Pull  = GPIO_PULLUP;
    led_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED0_GPIO_PORT, &led_handler);

    led_handler.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT, &led_handler);
    
    /* 初始LED0亮，LED1灭 */
    LED0(0);LED1(1);
}
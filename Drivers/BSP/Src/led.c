#include "led.h"

void led_init(void) {

    GPIO_InitTypeDef gpio_init;

    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();

    gpio_init.Pin   = LED0_GPIO_PIN;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull  = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init);

    gpio_init.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init);
    
    /* 初始LED0亮，LED1灭 */
    LED0(0);LED1(1);
}
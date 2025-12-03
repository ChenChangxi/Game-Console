#include "led.h"

GPIO_InitTypeDef  led_handler;
TIM_HandleTypeDef led_time_handler;

void led_init(uint16_t div, uint16_t cou) {

    LED_GPIO_CLK_ENABLE();

    led_handler.Pin   = LED_GPIO_PIN;
    led_handler.Mode  = GPIO_MODE_OUTPUT_PP;
    led_handler.Pull  = GPIO_PULLUP;
    led_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &led_handler);

    led_time_handler.Instance         = LED_TIME;
    led_time_handler.Init.Prescaler   = div;
    led_time_handler.Init.Period      = cou;
    led_time_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&led_time_handler);
    HAL_TIM_Base_Start_IT(&led_time_handler);

    /* 初始LED0亮，LED1灭 */
    LED0(0);LED1(1);
}

void LED_DAC_IRQHandler(void) {HAL_TIM_IRQHandler(&led_time_handler);}
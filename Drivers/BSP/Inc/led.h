/* LED驱动 */

#ifndef __LED_H
#define __LED_H

#include "sys.h"

/* 引脚和时钟 */
#define LED_GPIO_PORT          GPIOB
#define LED_GPIO_PIN           GPIO_PIN_0 | GPIO_PIN_1
#define LED_TIME               TIM6
#define LED_TIME_IRQn          TIM6_DAC_IRQn
#define LED_TIME_IRQHandler    TIM6_IRQHandler
#define LED_GPIO_CLK_ENABLE()  do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define LED_TIME_CLK_ENABLE()  do {__HAL_RCC_TIM6_CLK_ENABLE();}  while (0)

#define LED0_GPIO_PIN          GPIO_PIN_1   /* RED */
#define LED1_GPIO_PIN          GPIO_PIN_0   /* GREEN */

/* 共享中断服务函数 */
#define TIM6_IRQHandler        LED_DAC_IRQHandler
#define LED_DAC_IRQHandler     TIM6_DAC_IRQHandler

/* LED读写定义 */
#define LED0(x) do {HAL_GPIO_WritePin(LED_GPIO_PORT, LED0_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)
#define LED1(x) do {HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* LED翻转定义 */
#define LED0_TOGGLE() do {HAL_GPIO_TogglePin(LED_GPIO_PORT, LED0_GPIO_PIN);} while (0)
#define LED1_TOGGLE() do {HAL_GPIO_TogglePin(LED_GPIO_PORT, LED1_GPIO_PIN);} while (0)

/* 初始化LED */
void led_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern GPIO_InitTypeDef  led_handler;
extern TIM_HandleTypeDef led_time_handler;

#endif
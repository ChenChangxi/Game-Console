/* LED驱动 */

#ifndef __LED_H
#define __LED_H

#include "sys.h"

/* 引脚和时钟 */
#define LED_GPIO_PORT          GPIOB
#define LED_GPIO_PIN           GPIO_PIN_0 | GPIO_PIN_1
#define LED_GPIO_CLK_ENABLE()  do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)

#define LED0_GPIO_PIN          GPIO_PIN_1   /* RED */
#define LED1_GPIO_PIN          GPIO_PIN_0   /* GREEN */

/* LED读写定义 */
#define LED0(x) do {HAL_GPIO_WritePin(LED_GPIO_PORT, LED0_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)
#define LED1(x) do {HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* LED翻转定义 */
#define LED0_TOGGLE() do {HAL_GPIO_TogglePin(LED_GPIO_PORT, LED0_GPIO_PIN);} while (0)
#define LED1_TOGGLE() do {HAL_GPIO_TogglePin(LED_GPIO_PORT, LED1_GPIO_PIN);} while (0)

/* 初始化LED */
void led_init(void);

/* 变量声明 */
extern GPIO_InitTypeDef led_handler;

#endif
/* LED驱动 */

#ifndef __LED_H
#define __LED_H

#include "sys.h"

/* 引脚和时钟 */
#define LED0_GPIO_PORT          GPIOF
#define LED0_GPIO_PIN           GPIO_PIN_9   /* RED */
#define LED0_GPIO_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)    /* 方便调试的技巧 */

#define LED1_GPIO_PORT          GPIOF
#define LED1_GPIO_PIN           GPIO_PIN_10  /* GREEN */
#define LED1_GPIO_CLK_ENABLE()  do {__HAL_RCC_GPIOF_CLK_ENABLE();} while (0)

/* LED读写定义 */
#define LED0(x) do {HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)
#define LED1(x) do {HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)

/* LED翻转定义 */
#define LED0_TOGGLE() do {HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN);} while (0)
#define LED1_TOGGLE() do {HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN);} while (0)

/* 初始化LED */
void led_init(void);

#endif
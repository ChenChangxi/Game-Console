/* 蜂鸣器驱动 */

#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"

/* 引脚和时钟 */
#define BEEP_GPIO_PORT          GPIOF
#define BEEP_GPIO_PIN           GPIO_PIN_8
#define BEEP_GPIO_CLK_ENABLE()  do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)

/* 读写和翻转 */
#define BEEP(x) do {HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET);} while (0)
#define BEEP_TOGGLE() do {HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN);} while (0)

/* 初始化蜂鸣器 */
void beep_init(void);

#endif
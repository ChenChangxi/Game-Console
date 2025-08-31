/* 看门狗驱动 */

#ifndef __WDG_H
#define __WDG_H

#include "sys.h"

/* 独立看门狗 */
#define IWDG                IWDG1

/* 窗口看门狗 */
#define WWDG                WWDG1
#define WWDG_IRQn           WWDG_IRQn
#define WWDG_IRQHandler     WWDG_IRQHandler
#define WWDG_CLK_ENABLE()   do {__HAL_RCC_WWDG_CLK_ENABLE();} while (0)

/* 初始化独立看门狗 */
void iwdg_init(uint8_t div, uint16_t load);

/* 喂狗（IWDG）*/
void iwdg_feed(void);

/* 初始化窗口看门狗 */
void wwdg_init(uint8_t div, uint8_t cou, uint8_t win);

/* 喂狗（WWDG）*/
void wwdg_feed(void);

/* 变量声明 */
extern uint8_t feed_iwdg[];
extern uint8_t feed_wwdg[];
extern uint8_t iwdg_reset[];
extern uint8_t wwdg_reset[];
extern uint8_t exte_reset[];
extern uint8_t stat_reset[];
extern IWDG_HandleTypeDef iwdg_handler;
extern WWDG_HandleTypeDef wwdg_handler;

#endif
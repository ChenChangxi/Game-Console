/* 看门狗驱动 */

#ifndef __WDG_H
#define __WDG_H

#include "sys.h"
#include "led.h"

/* 字符串长度 */
#define WDG_LEN 14

/* 初始化独立看门狗 */
void iwdg_init(uint8_t div, uint16_t load);

/* 喂狗（IWDG）*/
void iwdg_feed(void);

/* 初始化窗口看门狗 */
void wwdg_init(uint8_t div, uint8_t cou, uint8_t win);

/* 喂狗（WWDG）*/
void wwdg_feed(void);

/* 变量声明 */
extern uint8_t feed_iwdg[WDG_LEN];     /* 请喂iwdg（UTF-8）*/
extern uint8_t feed_wwdg[WDG_LEN];     /* 请喂wwdg（UTF-8）*/
extern uint8_t iwdg_reset[WDG_LEN];    /* iwdg复位（UTF-8）*/
extern uint8_t wwdg_reset[WDG_LEN];    /* wwdg复位（UTF-8）*/
extern uint8_t exte_reset[WDG_LEN];    /* 外部复位（UTF-8）*/
extern uint8_t stat_reset[WDG_LEN];    /* 上电复位（UTF-8）*/
extern IWDG_HandleTypeDef iwdg_handler;
extern WWDG_HandleTypeDef wwdg_handler;

#endif
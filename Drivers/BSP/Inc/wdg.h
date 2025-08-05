/* 看门狗驱动 */

#ifndef __WDG_H
#define __WDG_H

#include "sys.h"

/* 字符串长度 */
#define IWDG_FEED 11

/* 初始化独立看门狗 */
void iwdg_init(uint8_t div, uint16_t load);

/* 喂狗（IWDG）*/
void iwdg_feed(void);

/* 变量声明 */
extern uint8_t ask[IWDG_FEED];    /* 请喂狗（UTF-8）*/
extern uint8_t done[IWDG_FEED];   /* 已喂狗（UTF-8）*/
extern IWDG_HandleTypeDef iwdg_handler;

#endif
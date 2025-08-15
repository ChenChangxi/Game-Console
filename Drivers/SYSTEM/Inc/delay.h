/* 系统滴答定时器 */

#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"

extern uint16_t cyc_us;
extern uint16_t cou_ms;

/* 初始化系统滴答定时器 */
void delay_init(uint16_t sysclk);

/* 微秒延时 */
void delay_us(uint32_t us);

/* 毫秒延时 */
void delay_ms(uint16_t ms);

#endif
/* RTC驱动 */

#ifndef __RTC_H
#define __RTC_H

#include "sys.h"

/* RTC */
#define RTC_BACK_UP       0x20260202
#define RTC_FORMAT        RTC_FORMAT_BIN
#define RTC_CLK_ENABLE()  do {__HAL_RCC_RTC_CLK_ENABLE();} while (0)

/* RTC初始化 */
void rtc_init(void);

/* 获取时间 */
void rtc_get_date(uint8_t *yer, uint8_t *mon, uint8_t *wek, uint8_t *day);

/* 获取日期 */
void rtc_get_time(uint8_t *hou, uint8_t *min, uint8_t *sec, uint8_t *sub);

/* 设置闹钟 */
void rtc_set_alarm(uint8_t wek, uint8_t hou, uint8_t min, uint8_t sec);

/* 变量声明 */
extern RTC_DateTypeDef   rtc_date_handler;
extern RTC_TimeTypeDef   rtc_time_handler;
extern RTC_AlarmTypeDef  rtc_alrm_handler;
extern RTC_HandleTypeDef rtc_init_handler;

#endif
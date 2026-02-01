#include "rtc.h"

RTC_HandleTypeDef rtc_init_handler;


void rtc_init(void) {

    RTC_DateTypeDef rtc_date_handler;
    RTC_TimeTypeDef rtc_time_handler;

    rtc_init_handler.Instance            = RTC;
    rtc_init_handler.Init.AsynchPrediv   = 
    rtc_init_handler.Init.SynchPrediv    = 
    rtc_init_handler.Init.HourFormat     = RTC_HOURFORMAT_24;   /* 24小时制 */
    rtc_init_handler.Init.OutPut         =
    rtc_init_handler.Init.OutPutPolarity =
    rtc_init_handler.Init.OutPutRemap    =
    rtc_init_handler.Init.OutPutType     = 
    HAL_RTC_Init(&rtc_init_handler);

    rtc_date_handler.Year       =      /* 年 */
    rtc_date_handler.Month      =      /* 月 */
    rtc_date_handler.WeekDay    =      /* 星期 */
    rtc_date_handler.Date       =      /* 日 */
    HAL_RTC_SetDate(&rtc_init_handler, &rtc_date_handler, RTC_FORMAT_BIN);

    rtc_time_handler.Hours      =      /* 时 */
    rtc_time_handler.Minutes    =      /* 分 */
    rtc_time_handler.Seconds    =      /* 秒 */
    rtc_time_handler.SubSeconds =      /* 亚秒 */
    rtc_time_handler.TimeFormat = 
    HAL_RTC_SetTime(&rtc_init_handler, &rtc_time_handler, RTC_FORMAT_BIN);
}
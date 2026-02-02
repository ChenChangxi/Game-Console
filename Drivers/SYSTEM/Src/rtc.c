#include "rtc.h"

RTC_DateTypeDef   rtc_date_handler;
RTC_TimeTypeDef   rtc_time_handler;
RTC_AlarmTypeDef  rtc_alrm_handler;
RTC_HandleTypeDef rtc_init_handler;

void rtc_init(void) {

    uint32_t bkup;

    rtc_init_handler.Instance            = RTC;
    rtc_init_handler.Init.AsynchPrediv   = 
    rtc_init_handler.Init.SynchPrediv    = 
    rtc_init_handler.Init.HourFormat     = RTC_HOURFORMAT_24;   /* 24小时制 */
    rtc_init_handler.Init.OutPut         =
    rtc_init_handler.Init.OutPutPolarity =
    rtc_init_handler.Init.OutPutRemap    =
    rtc_init_handler.Init.OutPutType     = 
    HAL_RTC_Init(&rtc_init_handler);

    bkup = HAL_RTCEx_BKUPRead(&rtc_init_handler, 0);

    if (bkup != RTC_BACK_UP) {             /* 设置时间（一次）*/

        rtc_date_handler.Year       =      /* 年 */
        rtc_date_handler.Month      =      /* 月 */
        rtc_date_handler.WeekDay    =      /* 星期 */
        rtc_date_handler.Date       =      /* 日 */
        HAL_RTC_SetDate(&rtc_init_handler, &rtc_date_handler, RTC_FORMAT);

        rtc_time_handler.Hours      =      /* 时 */
        rtc_time_handler.Minutes    =      /* 分 */
        rtc_time_handler.Seconds    =      /* 秒 */
        rtc_time_handler.SubSeconds =      /* 亚秒 */
        rtc_time_handler.TimeFormat = 
        HAL_RTC_SetTime(&rtc_init_handler, &rtc_time_handler, RTC_FORMAT);

        HAL_RTCEx_BKUPWrite(&rtc_init_handler, 0, RTC_BACK_UP);
    }
}

void rtc_get_date(uint8_t *yer, uint8_t *mon, uint8_t *wek, uint8_t *day) {

    HAL_RTC_GetDate(&rtc_init_handler, &rtc_date_handler, RTC_FORMAT);
    *yer = rtc_date_handler.Year;
    *mon = rtc_date_handler.Month;
    *wek = rtc_date_handler.WeekDay;
    *day = rtc_date_handler.Date;
}

void rtc_get_time(uint8_t *hou, uint8_t *min, uint8_t *sec, uint8_t *sub) {

    HAL_RTC_GetTime(&rtc_init_handler, &rtc_time_handler, RTC_FORMAT);
    *hou = rtc_time_handler.Hours;
    *min = rtc_time_handler.Minutes;
    *sec = rtc_time_handler.Seconds;
    *sub = rtc_time_handler.SubSeconds;
}

void rtc_set_alarm(uint8_t wek, uint8_t hou, uint8_t min, uint8_t sec) {

    rtc_alrm_handler.AlarmTime.Hours     = hou;
    rtc_alrm_handler.AlarmTime.Minutes   = min;
    rtc_alrm_handler.AlarmTime.Seconds   = sec;

    rtc_alrm_handler.Alarm               = 
    rtc_alrm_handler.AlarmMask           = 
    rtc_alrm_handler.AlarmSubSecondMask  = 
    rtc_alrm_handler.AlarmDateWeekDay    = wek;
    rtc_alrm_handler.AlarmDateWeekDaySel = 

    HAL_RTC_SetAlarm_IT(&rtc_init_handler, &rtc_alrm_handler, RTC_FORMAT);   /* 设置闹钟才开中断 */
}

void RTC_WKUP_IRQHandler(void) {}

void RTC_Alarm_IRQHandler(void) {HAL_RTC_AlarmIRQHandler(&rtc_init_handler);}
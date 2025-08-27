#include "key.h"
#include "timer.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(5, 192, 2, 4);
    delay_init(480);
    led_init();
    key_init();
    usart_init(115200);
    iwdg_init(IWDG_PRESCALER_8, 140);
    wwdg_init(WWDG_PRESCALER_8, 0x7F, 0x5F);
    deay_time_init(12000 - 1, 10000 - 1, 7200 - 1, 1000 - 1);     /* 500ms,30ms */
    comp_time_init(120 - 1, 1000 - 1);                            /* 500us */
    capt_time_init(240 - 1, 65535 - 1);                           /* 1us */
    usart_transmit(feed_iwdg, strlen(feed_iwdg));
    usart_transmit(feed_wwdg, strlen(feed_wwdg));
    
    /* 复位方式 */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDG1RST)) usart_transmit(wwdg_reset, strlen(wwdg_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDG1RST)) usart_transmit(iwdg_reset, strlen(iwdg_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))   usart_transmit(stat_reset, strlen(stat_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))   usart_transmit(exte_reset, strlen(exte_reset));
    __HAL_RCC_CLEAR_RESET_FLAGS();                                /* 清标志（会积累）*/

    while (1) {

        delay_ms(5);
        __HAL_TIM_SET_COMPARE(&bln_time_handler, BLN_TIME_CHANNEL, get_pers());              /* 改变PWM占空比 */
        if (uart_stat & 0x8000) {usart_transmit(data, uart_stat & 0x3fff);uart_stat = 0;}    /* 低14位为长度 */
        if (time_stat & 0x8000) {
            
            time_tota = (time_stat & 0x3fff) * 65536 + time_coun;
            snprintf(time_data, 11 + get_digs(time_tota) + 1, "按下:%uus\r\n", time_tota);   /* size需包含\0 */
            usart_transmit(time_data, 11 + get_digs(time_tota));time_stat = 0;
        }
    }
}
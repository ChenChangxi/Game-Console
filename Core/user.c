#include "key.h"
#include "wdg.h"
#include "timer.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(5, 192, 2, 4);
    delay_init(480);
    led_init();
    key_init();
    usart_init(115200);
    iwdg_init(IWDG_PRESCALER_8, 120);
    wwdg_init(WWDG_PRESCALER_8, 0x7F, 0x5F);
    base_time_init(10000 - 1, 12000 -1);                                     /* 延时500ms */
    usart_transmit(feed_iwdg, WDG_LEN);
    usart_transmit(feed_wwdg, WDG_LEN);
    
    /* 复位方式 */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDG1RST)) usart_transmit(wwdg_reset, WDG_LEN);
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDG1RST)) usart_transmit(iwdg_reset, WDG_LEN);
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))   usart_transmit(stat_reset, WDG_LEN);
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))   usart_transmit(exte_reset, WDG_LEN);
    __HAL_RCC_CLEAR_RESET_FLAGS();                                           /* 清标志（会积累）*/

    while (1) {

        delay_ms(30);wwdg_feed();iwdg_feed();
        if (stat & 0x8000) {usart_transmit(data, stat & 0x3fff);stat = 0;}   /* 低14位为长度 */
    }
}
#include "key.h"
#include "lcd.h"
#include "fmc.h"
#include "tpad.h"
#include "oled.h"
#include "timer.h"
#include "usart.h"
#include "stdio.h"
#include "sdram.h"
#include "string.h"
#include "at24c02.h"
#include "ap3216c.h"
#include "pcf8574.h"

int main(void) {

    HAL_Init();
    sys_stm32_clock_init(5, 192, 2, 4);
    delay_init(480);
    led_init();
    key_init();
    iic_init();
    fmc_init();
    lcd_init();
    oled_init();
    sdram_init();
    at24c02_init();
    ap3216c_init();
    pcf8574_init();
    usart_init(115200);
    iwdg_init(IWDG_PRESCALER_8, 140);
    wwdg_init(WWDG_PRESCALER_8, 0x7f, 0x5f);
    tpad_init(6 - 1);                                             /* 25ns */
    deay_time_init(12000 - 1, 10000 - 1, 7200 - 1, 1000 - 1);     /* 500ms,30ms */
    mast_time_init(1 - 1, 5 - 1);                                 /* 500ns */
    comp_time_init(1 - 1, 1000 - 1, 0xed);                        /* 500us,12us */
    capt_time_init(240 - 1, 0xffffffff - 1);                      /* 1us */
    usart_transmit(feed_iwdg, strlen(feed_iwdg));
    usart_transmit(feed_wwdg, strlen(feed_wwdg));
    
    /* 复位方式 */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDG1RST)) usart_transmit(wwdg_reset, strlen(wwdg_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDG1RST)) usart_transmit(iwdg_reset, strlen(iwdg_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))   usart_transmit(stat_reset, strlen(stat_reset));
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))   usart_transmit(exte_reset, strlen(exte_reset));
    __HAL_RCC_CLEAR_RESET_FLAGS();                                /* 清标志（会积累）*/

    while (1) {

        if (time_stat & 0x8000) {
            
            uint8_t  time_data[KIC_TIME_DATA_SIZE] = {0};
            uint32_t time_tota = (time_stat & 0x3fff) * 65536 + time_coun;
            snprintf(time_data, 11 + get_digs(time_tota) + 1, "按下:%uus\r\n", time_tota);   /* size需包含\0 */
            usart_transmit(time_data, 11 + get_digs(time_tota));time_stat = 0;
        }
        if (uart_stat & 0x8000) {

            uint16_t data_size = uart_stat & 0x3fff;
            snprintf(data + data_size, sizeof(data) - data_size, "\r\n");data_size += 2;uart_stat = 0;
            if (!strcmp(data, "show\r\n"))  {atc_read(0, data, atc_addr);usart_transmit(data, atc_addr);}
            else if (!strcmp(data, "erase\r\n"))  {

                usart_transmit(atc_ders, strlen(atc_ders));
                atc_write(0, atc_erse, 256);atc_addr = 0;atc_write(0xff, &atc_addr, 1);

            } else if (atc_addr + data_size > 0xfe) usart_transmit(atc_dout, strlen(atc_dout));
            else {atc_write(atc_addr, data, data_size);atc_addr += data_size;atc_write(0xff, &atc_addr, 1);}
        }
        if (ctor_coun > 120) pcf_write(0, BEEP);else pcf_write(1, BEEP);
    }
}
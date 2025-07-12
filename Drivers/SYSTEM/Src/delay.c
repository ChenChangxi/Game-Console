#include "delay.h"

void delay_init(uint16_t sysclk) {

    SysTick -> CTRL = 0;
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
    cyc_us = sysclk / 8;
}

void delay_us(uint32_t us) {

    uint32_t ctrl;
    SysTick -> LOAD = us * cyc_us;
    SysTick -> VAL  = 0x00;
    SysTick -> CTRL |= 1<<0;
    do {
        ctrl = SysTick -> CTRL;
    } while ((ctrl & 0x01) && !(ctrl & (1<<16)));
    SysTick -> CTRL &= ~(1<<0);
    SysTick -> VAL = 0x00;
}

void delay_ms(uint16_t ms) {
    
    uint32_t ins = ms / 700;     /* delay_us最大延时为798ms */
    uint32_t rec = ms % 700;
    while (ins--) delay_us(700 * 1000);
    if (rec) delay_us(rec * 1000);
}
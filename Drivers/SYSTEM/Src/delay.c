#include "delay.h"

uint16_t cyc_us = 0;
uint16_t cou_ms = 200;

void delay_init(uint16_t sysclk) {

    SysTick -> CTRL = 0;
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);   /* 实际是D1域而不是AHB */
    cyc_us = sysclk / 8;
}

void delay_us(uint32_t us) {

    uint32_t ctrl;
    SysTick -> LOAD = us * cyc_us;
    SysTick -> VAL  = 0x00;
    SysTick -> CTRL |= 1<<0;
    do {ctrl = SysTick -> CTRL;} while ((ctrl & 0x01) && !(ctrl & (1<<16)));
    SysTick -> CTRL &= ~(1<<0);
    SysTick -> VAL = 0x00;
}

void delay_ms(uint16_t ms) {
    
    uint32_t ins = ms / cou_ms;     /* delay_us最大延时为279ms */
    uint32_t rec = ms % cou_ms;
    while (ins--) delay_us(cou_ms * 1000);
    if (rec) delay_us(rec * 1000);
}
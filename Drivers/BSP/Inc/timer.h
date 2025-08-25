/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "led.h"
#include "stdlib.h"
#include "wdg.h"

/* 基本定时器 */
#define LED_TIME                 TIM3
#define LED_TIME_IRQn            TIM3_IRQn
#define LED_TIME_IRQHandler      TIM3_IRQHandler
#define LED_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM3_CLK_ENABLE();} while (0)

#define WDG_TIME                 TIM4
#define WDG_TIME_IRQn            TIM4_IRQn
#define WDG_TIME_IRQHandler      TIM4_IRQHandler
#define WDG_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM4_CLK_ENABLE();} while (0)

/* 通用定时器 */
#define BLN_TIME                 TIM2
#define BLN_TIME_CHANNEL         TIM_CHANNEL_2
#define BLN_TIME_PORT            GPIOB
#define BLN_TIME_PIN             GPIO_PIN_3
#define BLN_TIME_AF              GPIO_AF1_TIM2
#define BLN_GPIO_CLK_ENABLE()    do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define BLN_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM2_CLK_ENABLE();}  while (0)

/* 0~400折返 */
uint16_t get_pers(void);

/* 定时器初始化 */
void base_time_init(uint16_t led_div, uint16_t led_cou, 
                    uint16_t wdg_div, uint16_t wdg_cou);
void gene_time_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern uint16_t           ins;
extern TIM_HandleTypeDef  led_time_handler;
extern TIM_HandleTypeDef  wdg_time_handler;
extern TIM_HandleTypeDef  bln_time_handler;
extern GPIO_InitTypeDef   bln_gpio_handler;
extern TIM_OC_InitTypeDef bln_pwm_handler;

#endif
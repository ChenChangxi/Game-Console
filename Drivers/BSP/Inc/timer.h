/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "led.h"
#include "stdlib.h"
#include "wdg.h"

/* 定时中断 */
#define LED_TIME                    TIM13
#define LED_TIME_IRQn               TIM8_UP_TIM13_IRQn
#define LED_TIME_IRQHandler         TIM13_IRQHandler
#define LED_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM13_CLK_ENABLE();} while (0)

#define WDG_TIME                    TIM14
#define WDG_TIME_IRQn               TIM8_TRG_COM_TIM14_IRQn
#define WDG_TIME_IRQHandler         TIM14_IRQHandler
#define WDG_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM14_CLK_ENABLE();} while (0)

/* 输出比较 */
#define BLN_TIME                    TIM8
#define BLN_TIME_CHANNEL            TIM_CHANNEL_2
#define BLN_TIME_PORT               GPIOC
#define BLN_TIME_PIN                GPIO_PIN_7
#define BLN_TIME_AF                 GPIO_AF3_TIM8
#define BLN_TIME_IRQn               TIM8_UP_TIM13_IRQn
#define BLN_TIME_IRQHandler         TIM8_UP_IRQHandler
#define BLN_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOC_CLK_ENABLE();} while (0)
#define BLN_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM8_CLK_ENABLE();}  while (0)

/* 输入捕获 */
#define KIC_TIME                    TIM5
#define KIC_TIME_CHANNEL            TIM_CHANNEL_2
#define KIC_TIME_PORT               GPIOA
#define KIC_TIME_PIN                GPIO_PIN_0
#define KIC_TIME_AF                 GPIO_AF2_TIM5
#define KIC_TIME_IRQn               TIM5_IRQn
#define KIC_TIME_IRQHandler         TIM5_IRQHandler
#define KIC_TIME_DATA_SIZE          25
#define KIC_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define KIC_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM5_CLK_ENABLE();}  while (0)

/* 主定时器 */
#define MST_TIME                    TIM4
#define MST_TIME_PORT               GPIOE
#define MST_TIME_PIN                GPIO_PIN_0
#define MST_TIME_AF                 GPIO_AF2_TIM4
#define MST_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOE_CLK_ENABLE();} while (0)
#define MST_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM4_CLK_ENABLE();}  while (0)

/* 共享中断服务函数 */
#define TIM13_IRQHandler            LED_BLN_UP_IRQHandler
#define TIM14_IRQHandler            WDG_XXX_TRG_COM_IRQHandler
#define TIM8_UP_IRQHandler          LED_BLN_UP_IRQHandler

#define LED_BLN_UP_IRQHandler       TIM8_UP_TIM13_IRQHandler
#define WDG_XXX_TRG_COM_IRQHandler  TIM8_TRG_COM_TIM14_IRQHandler

/* 0~100折返 */
uint16_t get_pers(uint16_t per);

/* 获取整数位数 */
uint16_t get_digs(uint32_t time_tota);

/* 定时器初始化 */
void deay_time_init(uint16_t led_div, uint16_t led_cou, 
                    uint16_t wdg_div, uint16_t wdg_cou);
void mast_time_init(uint16_t div, uint16_t cou);
void comp_time_init(uint16_t div, uint16_t cou);
void capt_time_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern uint16_t ins;
extern uint16_t time_stat;       /* 0为发送状态，1为边沿状态，2~15为计数周期数 */
extern uint16_t time_coun;       /* 计数器计数值 */
extern TIM_HandleTypeDef led_time_handler;
extern TIM_HandleTypeDef wdg_time_handler;
extern TIM_HandleTypeDef bln_time_handler;
extern TIM_HandleTypeDef kic_time_handler;
extern TIM_HandleTypeDef mst_time_handler;

#endif
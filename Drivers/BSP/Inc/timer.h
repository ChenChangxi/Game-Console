/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "led.h"
#include "stdlib.h"
#include "wdg.h"

/* 定时中断 */
#define LED_TIME                 TIM16
#define LED_TIME_IRQn            TIM16_IRQn
#define LED_TIME_IRQHandler      TIM16_IRQHandler
#define LED_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM16_CLK_ENABLE();} while (0)

#define WDG_TIME                 TIM17
#define WDG_TIME_IRQn            TIM17_IRQn
#define WDG_TIME_IRQHandler      TIM17_IRQHandler
#define WDG_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM17_CLK_ENABLE();} while (0)

/* 输出比较 */
#define BLN_TIME                 TIM2
#define BLN_TIME_CHANNEL         TIM_CHANNEL_2
#define BLN_TIME_PORT            GPIOB
#define BLN_TIME_PIN             GPIO_PIN_3
#define BLN_TIME_AF              GPIO_AF1_TIM2
#define BLN_TIME_IRQn            TIM2_IRQn
#define BLN_TIME_IRQHandler      TIM2_IRQHandler
#define BLN_GPIO_CLK_ENABLE()    do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define BLN_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM2_CLK_ENABLE();}  while (0)

/* 输入捕获 */
#define KIC_TIME                 TIM5
#define KIC_TIME_CHANNEL         TIM_CHANNEL_2
#define KIC_TIME_PORT            GPIOA
#define KIC_TIME_PIN             GPIO_PIN_0
#define KIC_TIME_AF              GPIO_AF2_TIM5
#define KIC_TIME_IRQn            TIM5_IRQn
#define KIC_TIME_IRQHandler      TIM5_IRQHandler
#define KIC_TIME_DATA_SIZE       25
#define KIC_GPIO_CLK_ENABLE()    do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define KIC_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM5_CLK_ENABLE();}  while (0)

/* 主定时器 */
#define MST_TIME                 TIM3
#define MST_TIME_PORT            GPIOD
#define MST_TIME_PIN             GPIO_PIN_2
#define MST_TIME_AF              GPIO_AF2_TIM3
#define MST_GPIO_CLK_ENABLE()    do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define MST_TIME_CLK_ENABLE()    do {__HAL_RCC_TIM3_CLK_ENABLE();}  while (0)

/* 0~100折返 */
uint16_t get_pers(uint16_t per);

/* 获取整数位数 */
uint8_t get_digs(uint32_t time_tota);

/* 定时器初始化 */
void deay_time_init(uint16_t led_div, uint16_t led_cou, 
                    uint16_t wdg_div, uint16_t wdg_cou);
void comp_time_init(uint16_t div, uint16_t cou);
void capt_time_init(uint16_t div, uint16_t cou);
void mast_time_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern uint16_t                ins;
extern uint16_t                cnt;
extern uint16_t                time_stat;       /* 0为发送状态，1为边沿状态，2~15为计数周期数 */
extern uint16_t                time_coun;       /* 计数器计数值 */
extern uint32_t                time_tota;       /* 总时间（us）*/
extern uint8_t                 time_data[KIC_TIME_DATA_SIZE];      /* 发送串口的字节流 */
extern TIM_HandleTypeDef       led_time_handler;
extern TIM_HandleTypeDef       wdg_time_handler;
extern TIM_HandleTypeDef       bln_time_handler;
extern TIM_HandleTypeDef       kic_time_handler;
extern TIM_HandleTypeDef       mst_time_handler;
extern GPIO_InitTypeDef        bln_gpio_handler;
extern GPIO_InitTypeDef        kic_gpio_handler;
extern GPIO_InitTypeDef        mst_gpio_handler;
extern TIM_OC_InitTypeDef      bln_pwm_handler;
extern TIM_IC_InitTypeDef      kic_cap_handler;
extern TIM_SlaveConfigTypeDef  bln_clk_handler;
extern TIM_ClockConfigTypeDef  mst_clk_handler;
extern TIM_MasterConfigTypeDef mst_cfg_handler;

#endif
/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "stdlib.h"

/* 输出比较 */
#define BLN_TIME                    TIM1
#define BLN_TIME_PWM_CHANNEL        TIM_CHANNEL_3
#define BLN_TIME_PHASEX_CHANNEL     TIM_CHANNEL_1
#define BLN_TIME_PHASEY_CHANNEL     TIM_CHANNEL_2
#define BLN_TIME_PHASEX_PIN         GPIO_PIN_8
#define BLN_TIME_PHASEY_PIN         GPIO_PIN_9
#define BLN_TIME_PHASE_PIN          GPIO_PIN_7
#define BLN_TIME_PORT               GPIOA
#define BLC_TIME_PORT               GPIOB         /* 互补通道 */
#define BLB_TIME_PORT               GPIOA         /* 刹车断路 */
#define BLN_TIME_PIN                GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
#define BLC_TIME_PIN                GPIO_PIN_15
#define BLB_TIME_PIN                GPIO_PIN_6
#define BLN_TIME_AF                 GPIO_AF1_TIM1
#define BLN_TIME_UP_IRQn            TIM1_UP_IRQn
#define BLN_TIME_CC_IRQn            TIM1_CC_IRQn
#define BLN_TIME_UP_IRQHandler      TIM1_UP_IRQHandler
#define BLN_TIME_CC_IRQHandler      TIM1_CC_IRQHandler
#define BLN_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define BLC_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define BLB_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define BLN_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM1_CLK_ENABLE();}  while (0)

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
#define MST_TIME                    TIM3
#define MST_TIME_PORT               GPIOD
#define MST_TIME_PIN                GPIO_PIN_2
#define MST_TIME_AF                 GPIO_AF2_TIM3
#define MST_GPIO_CLK_ENABLE()       do {__HAL_RCC_GPIOD_CLK_ENABLE();} while (0)
#define MST_TIME_CLK_ENABLE()       do {__HAL_RCC_TIM3_CLK_ENABLE();}  while (0)

/* 0~1000折返 */
uint16_t get_pers(uint16_t per, uint16_t *cou);

/* 获取整数位数 */
uint16_t get_digs(uint32_t time_tota);

/* 定时器初始化 */
void mast_time_init(uint16_t div, uint16_t cou);
void comp_time_init(uint16_t div, uint16_t cou, uint16_t dea);
void capt_time_init(uint16_t div, uint32_t cou);

/* 变量声明 */
extern uint16_t ins;
extern uint16_t cnx;
extern uint16_t cny;
extern uint16_t time_stat;       /* 0为发送状态，1为边沿状态，2~15为计数周期数 */
extern uint16_t time_coun;       /* 计数器计数值 */
extern TIM_HandleTypeDef bln_time_handler;
extern TIM_HandleTypeDef kic_time_handler;
extern TIM_HandleTypeDef mst_time_handler;

#endif
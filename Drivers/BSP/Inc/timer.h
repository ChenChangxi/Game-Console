/* 定时器驱动 */

#ifndef __TIME_H
#define __TIME_H

#include "sys.h"
#include "led.h"
#include "stdlib.h"

/* 基本定时器 */
#define BASE_TIME                TIM7
#define BASE_TIME_IRQn           TIM7_IRQn
#define BASE_TIME_IRQHandler     TIM7_IRQHandler
#define BASE_TIME_CLK_ENABLE()   do {__HAL_RCC_TIM7_CLK_ENABLE();} while (0)

/* 通用定时器 */
#define GENE_TIME_PWM            TIM2
#define GENE_TIME_PWM_CHANNEL    TIM_CHANNEL_2
#define GENE_TIME_PWM_PORT       GPIOB
#define GENE_TIME_PWM_PIN        GPIO_PIN_3
#define GENE_TIME_PWM_AF         GPIO_AF1_TIM2
#define GENE_GPIO_PWM_ENABLE()   do {__HAL_RCC_GPIOB_CLK_ENABLE();} while (0)
#define GENE_TIME_PWM_ENABLE()   do {__HAL_RCC_TIM2_CLK_ENABLE();}  while (0)

/* 0~400折返 */
uint16_t get_pers(void);

/* 定时器初始化 */
void base_time_init(uint16_t div, uint16_t cou);
void gene_time_init(uint16_t div, uint16_t cou);

/* 变量声明 */
extern uint16_t           ins;
extern TIM_HandleTypeDef  base_time_handler;
extern TIM_HandleTypeDef  gene_time_handler;
extern GPIO_InitTypeDef   gene_gpio_handler;
extern TIM_OC_InitTypeDef gene_pwm_handler;

#endif
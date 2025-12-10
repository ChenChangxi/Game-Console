/* ADC驱动 */

#ifndef __ADC_H
#define __ADC_H

#include "sys.h"
#include "string.h"

/* ADC */
#define ADC                     ADC1
#define ADC_CHANNEL             5
#define ADC_SAMPLE              100
#define ADC_RANGE               16
#define ADC_SIZE                ADC_CHANNEL * ADC_SAMPLE
#define ADC_DMA_STREAM          DMA1_Stream1
#define ADC_DMA_REQUEST         DMA_REQUEST_ADC1
#define ADC_GPIO_PORT           GPIOA
#define ADC_GPIO_PIN            GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_7
#define ADC_TIME                TIM4
#define ADC_TIME_DIV            240 - 1
#define ADC_TIME_COU            100 - 1
#define ADC_DMA_IRQn            DMA1_Stream1_IRQn
#define ADC_DMA_IRQHandler      DMA1_Stream1_IRQHandler
#define ADC_CLK_ENABLE()        do {__HAL_RCC_ADC12_CLK_ENABLE();} while (0)
#define ADC_DMA_CLK_ENABLE()    do {__HAL_RCC_DMA1_CLK_ENABLE();}  while (0)
#define ADC_GPIO_CLK_ENABLE()   do {__HAL_RCC_GPIOA_CLK_ENABLE();} while (0)
#define ADC_TIME_CLK_ENABLE()   do {__HAL_RCC_TIM4_CLK_ENABLE();}  while (0)

/* ADC初始化 */
void adc_init(void);

/* ADC通道配置 */
void adc_config_channel(uint32_t cha, uint32_t ran, uint32_t sam);

/* 变量声明 */
extern uint8_t           adc_stat;
extern uint32_t          off[ADC_CHANNEL];
extern uint16_t          dat[ADC_SIZE], tem[ADC_SIZE];
extern ADC_HandleTypeDef adc_init_handler;
extern DMA_HandleTypeDef adc_dma_handler;
extern TIM_HandleTypeDef adc_time_handler;

#endif
/* DMA */

#ifndef __DMA_H
#define __DMA_H

#include "sys.h"

#define DMA_CLK_ENABLE() do {__HAL_RCC_DMA1_CLK_ENABLE();__HAL_RCC_DMA2_CLK_ENABLE();} while (0)

/* DMA初始化 */
void dma_init(void);

/* 外设配置DMA数据流 */
void dma_config();

/* 变量声明 */
extern DMA_HandleTypeDef dma_con_hanlder;

#endif
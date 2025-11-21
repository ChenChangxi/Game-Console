#include "dma.h"

DMA_HandleTypeDef dma_con_hanlder;

void dma_init(void) {DMA_CLK_ENABLE();}

void dma_config() {

    
    HAL_DMA_Init(&dma_con_hanlder);
}
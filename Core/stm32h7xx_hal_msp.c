#include "sd.h"
#include "led.h"
#include "wdg.h"
#include "lcd.h"
#include "rgb.h"
#include "adc.h"
#include "rtc.h"
#include "tpad.h"
#include "nand.h"
#include "qspi.h"
#include "timer.h"
#include "usart.h"
#include "sdram.h"

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART) {

        GPIO_InitTypeDef gpio_handler = {0};

        USART_CLK_ENABLE();
        USART_DMA_CLK_ENABLE();
        USART_GPIO_CLK_ENABLE();

        gpio_handler.Pin       = USART_GPIO_PIN;
        gpio_handler.Mode      = GPIO_MODE_AF_PP;
        gpio_handler.Alternate = USART_GPIO_AF;
        gpio_handler.Pull      = GPIO_PULLUP;
        gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(USART_GPIO_PORT, &gpio_handler);

        uart_dma_handler.Instance                 = USART_DMA_STREAM;
        uart_dma_handler.Init.Request             = USART_DMA_REQUEST;
        uart_dma_handler.Init.Priority            = DMA_PRIORITY_MEDIUM;
        uart_dma_handler.Init.Mode                = DMA_NORMAL;
        uart_dma_handler.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        uart_dma_handler.Init.PeriphInc           = DMA_PINC_DISABLE;
        uart_dma_handler.Init.MemInc              = DMA_MINC_ENABLE;
        uart_dma_handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        uart_dma_handler.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        uart_dma_handler.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
        uart_dma_handler.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        uart_dma_handler.Init.PeriphBurst         = DMA_PBURST_SINGLE;
        uart_dma_handler.Init.MemBurst            = DMA_MBURST_SINGLE;
        HAL_DMA_Init(&uart_dma_handler);
        __HAL_LINKDMA(&uart_handler, hdmatx, uart_dma_handler);

        HAL_NVIC_SetPriority(USART_IRQn, 3, 3);
        HAL_NVIC_SetPriority(USART_DMA_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART_IRQn);
        HAL_NVIC_EnableIRQ(USART_DMA_IRQn);
    }
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg) {

    if (hwwdg->Instance == WWDG) {

        WWDG_CLK_ENABLE();
        HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(WWDG_IRQn);
    }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == LED_TIME) {

        LED_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(LED_TIME_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(LED_TIME_IRQn);

    } else if (htim->Instance == WWDG_TIME) {

        WWDG_TIME_CLK_ENABLE();
        HAL_NVIC_SetPriority(WWDG_TIME_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(WWDG_TIME_IRQn);

    } else if (htim->Instance == MST_TIME) {

        GPIO_InitTypeDef mst_gpio_handler = {0};

        MST_GPIO_CLK_ENABLE();
        MST_TIME_CLK_ENABLE();

        mst_gpio_handler.Pin       = MST_TIME_PIN;
        mst_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        mst_gpio_handler.Alternate = MST_TIME_AF;
        mst_gpio_handler.Pull      = GPIO_PULLDOWN;
        mst_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MST_TIME_PORT, &mst_gpio_handler);
    }
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BLN_TIME) {

        GPIO_InitTypeDef bln_gpio_handler = {0};

        BLN_GPIO_CLK_ENABLE();
        BLC_GPIO_CLK_ENABLE();
        BLB_GPIO_CLK_ENABLE();
        BLN_TIME_CLK_ENABLE();

        bln_gpio_handler.Pin       = BLN_TIME_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        bln_gpio_handler.Alternate = BLN_TIME_AF;
        bln_gpio_handler.Pull      = GPIO_PULLDOWN;
        bln_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLC_TIME_PIN;
        HAL_GPIO_Init(BLC_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLB_TIME_PIN;
        HAL_GPIO_Init(BLB_TIME_PORT, &bln_gpio_handler);

        bln_gpio_handler.Pin       = BLN_TIME_PHASE_PIN;
        bln_gpio_handler.Mode      = GPIO_MODE_OUTPUT_PP;
        HAL_GPIO_Init(BLN_TIME_PORT, &bln_gpio_handler);

        HAL_NVIC_EnableIRQ(BLN_TIME_UP_IRQn);
        HAL_NVIC_EnableIRQ(BLN_TIME_CC_IRQn);
        HAL_NVIC_SetPriority(BLN_TIME_UP_IRQn, 3, 1);
        HAL_NVIC_SetPriority(BLN_TIME_CC_IRQn, 3, 1);
    }
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {

    if (htim->Instance == KIC_TIME) {

        GPIO_InitTypeDef kic_gpio_handler = {0};

        KIC_GPIO_CLK_ENABLE();
        KIC_TIME_CLK_ENABLE();

        kic_gpio_handler.Pin       = KIC_TIME_PIN;
        kic_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        kic_gpio_handler.Alternate = KIC_TIME_AF;
        kic_gpio_handler.Pull      = GPIO_PULLDOWN;
        kic_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(KIC_TIME_PORT, &kic_gpio_handler);
        HAL_NVIC_EnableIRQ(KIC_TIME_IRQn);
        HAL_NVIC_SetPriority(KIC_TIME_IRQn, 3, 2);

    } else if (htim->Instance == TPAD_TIME) {

        GPIO_InitTypeDef tpad_gpio_handler = {0};

        TPAD_GPIO_CLK_ENABLE();
        TPAD_TIME_CLK_ENABLE();

        tpad_gpio_handler.Pin       = TPAD_GPIO_PIN;
        tpad_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        tpad_gpio_handler.Alternate = TPAD_GPIO_AF;
        tpad_gpio_handler.Pull      = GPIO_NOPULL;
        tpad_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(TPAD_GPIO_PORT, &tpad_gpio_handler);
        HAL_NVIC_EnableIRQ(TPAD_TIME_IRQn);
        HAL_NVIC_SetPriority(TPAD_TIME_IRQn, 3, 3);
    }
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram) {

    GPIO_InitTypeDef lcd_gpio_handler = {0};

    LCD_CON_CLK_ENABLE();
    LCD_BLN_CLK_ENABLE();

    lcd_gpio_handler.Pin       = LCD_CON_PIN;
    lcd_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    lcd_gpio_handler.Alternate = LCD_AF;
    lcd_gpio_handler.Pull      = GPIO_PULLUP;
    lcd_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_CON_PORT, &lcd_gpio_handler);

    lcd_gpio_handler.Pin       = LCD_BLN_PIN;
    lcd_gpio_handler.Mode      = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_BLN_PORT, &lcd_gpio_handler);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram) {

    GPIO_InitTypeDef sdram_gpio_handler = {0};

    SDRAM_CAS_CLK_ENABLE();
    SDRAM_RAS_CLK_ENABLE();
    SDRAM_WER_CLK_ENABLE();
    SDRAM_CSE_CLK_ENABLE();
    SDRAM_BAN_CLK_ENABLE();
    SDRAM_CLK_CLK_ENABLE();
    SDRAM_CKE_CLK_ENABLE();
    SDRAM_NBL_CLK_ENABLE();

    sdram_gpio_handler.Pin       = SDRAM_CAS_PIN;
    sdram_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    sdram_gpio_handler.Alternate = SDRAM_AF;
    sdram_gpio_handler.Pull      = GPIO_PULLUP;
    sdram_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDRAM_CAS_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_RAS_PIN;
    HAL_GPIO_Init(SDRAM_RAS_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_WER_PIN;
    HAL_GPIO_Init(SDRAM_WER_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CSE_PIN;
    HAL_GPIO_Init(SDRAM_CSE_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_BAN_PIN;
    HAL_GPIO_Init(SDRAM_BAN_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CLK_PIN;
    HAL_GPIO_Init(SDRAM_CLK_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_CKE_PIN;
    HAL_GPIO_Init(SDRAM_CKE_PORT, &sdram_gpio_handler);

    sdram_gpio_handler.Pin       = SDRAM_NBL_PIN;
    HAL_GPIO_Init(SDRAM_NBL_PORT, &sdram_gpio_handler);
}

void HAL_NAND_MspInit(NAND_HandleTypeDef *hnand) {

    GPIO_InitTypeDef nand_gpio_handler = {0};

    NAND_NWE_CLK_ENABLE();
    NAND_NOE_CLK_ENABLE();
    NAND_NCE_CLK_ENABLE();
    NAND_NWA_CLK_ENABLE();

    nand_gpio_handler.Pin       = NAND_NWE_PIN;
    nand_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    nand_gpio_handler.Alternate = NAND_AF;
    nand_gpio_handler.Pull      = GPIO_PULLUP;
    nand_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NAND_NWE_PORT, &nand_gpio_handler);

    nand_gpio_handler.Pin       = NAND_NOE_PIN;
    HAL_GPIO_Init(NAND_NOE_PORT, &nand_gpio_handler);

    nand_gpio_handler.Pin       = NAND_NCE_PIN;
    HAL_GPIO_Init(NAND_NCE_PORT, &nand_gpio_handler);

    nand_gpio_handler.Pin       = NAND_NWA_PIN;
    nand_gpio_handler.Mode      = GPIO_MODE_INPUT;      /* 低电平有效 */
    HAL_GPIO_Init(NAND_NWA_PORT, &nand_gpio_handler);
}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc) {

    GPIO_InitTypeDef ltdc_gpio_handler = {0};

    RGB_CLK_ENABLE();
    RGB_DAE_CLK_ENABLE();
    RGB_VSN_CLK_ENABLE();
    RGB_HSN_CLK_ENABLE();
    RGB_CLK_CLK_ENABLE();
    RGB_BLN_CLK_ENABLE();
    RGB_RED_CLK_ENABLE();
    RGB_GEN_CLK_ENABLE();
    RGB_BUE_CLK_ENABLE();
    RGB_DMA_CLK_ENABLE();

    ltdc_gpio_handler.Pin       = RGB_DAE_PIN;
    ltdc_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    ltdc_gpio_handler.Alternate = RGB_AF;
    ltdc_gpio_handler.Pull      = GPIO_PULLUP;
    ltdc_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RGB_DAE_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_HSN_PIN;
    HAL_GPIO_Init(RGB_HSN_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_VSN_PIN;
    HAL_GPIO_Init(RGB_VSN_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_CLK_PIN;
    HAL_GPIO_Init(RGB_CLK_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_RED_PIN;
    HAL_GPIO_Init(RGB_RED_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_BUE_PIN;
    HAL_GPIO_Init(RGB_BUE_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_GEN_PIN;
    HAL_GPIO_Init(RGB_GEN_PORT, &ltdc_gpio_handler);

    ltdc_gpio_handler.Pin       = RGB_BLN_PIN;
    ltdc_gpio_handler.Mode      = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(RGB_BLN_PORT, &ltdc_gpio_handler);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {

    if (hadc->Instance == ADC) {

        GPIO_InitTypeDef        adc_gpio_handler = {0};
        TIM_MasterConfigTypeDef mst_cfg_handler  = {0};

        ADC_CLK_ENABLE();
        ADC_DMA_CLK_ENABLE();
        ADC_GPIO_CLK_ENABLE();
        ADC_TIME_CLK_ENABLE();

        adc_gpio_handler.Pin   = ADC_GPIO_PIN;
        adc_gpio_handler.Mode  = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(ADC_GPIO_PORT, &adc_gpio_handler);

        adc_dma_handler.Instance                 = ADC_DMA_STREAM;
        adc_dma_handler.Init.Request             = ADC_DMA_REQUEST;
        adc_dma_handler.Init.Priority            = DMA_PRIORITY_HIGH;
        adc_dma_handler.Init.Mode                = DMA_CIRCULAR;
        adc_dma_handler.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        adc_dma_handler.Init.PeriphInc           = DMA_PINC_DISABLE;
        adc_dma_handler.Init.MemInc              = DMA_MINC_ENABLE;
        adc_dma_handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        adc_dma_handler.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
        adc_dma_handler.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
        adc_dma_handler.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        adc_dma_handler.Init.PeriphBurst         = DMA_PBURST_SINGLE;
        adc_dma_handler.Init.MemBurst            = DMA_MBURST_SINGLE;
        HAL_DMA_Init(&adc_dma_handler);
        __HAL_LINKDMA(&adc_init_handler, DMA_Handle, adc_dma_handler);

        adc_time_handler.Instance = ADC_TIME;
        adc_time_handler.Init.Prescaler         = ADC_TIME_DIV;
        adc_time_handler.Init.Period            = ADC_TIME_COU;
        adc_time_handler.Init.CounterMode       = TIM_COUNTERMODE_UP;
        adc_time_handler.Init.RepetitionCounter = 1 - 1;
        adc_time_handler.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
        adc_time_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
        HAL_TIM_Base_Init(&adc_time_handler);

        mst_cfg_handler.MasterOutputTrigger  = TIM_TRGO_UPDATE;
        mst_cfg_handler.MasterSlaveMode      = TIM_MASTERSLAVEMODE_DISABLE;
        HAL_TIMEx_MasterConfigSynchronization(&adc_time_handler, &mst_cfg_handler);

        HAL_NVIC_SetPriority(ADC_DMA_IRQn, 0, 2);
        HAL_NVIC_EnableIRQ(ADC_DMA_IRQn);
    }
}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi) {

    GPIO_InitTypeDef qspi_gpio_handler = {0};

    QSPI_CLK_ENABLE();
    QSPI_MDMA_ENABLE();
    QSPI_IOx_CLK_ENABLE();
    QSPI_CLK_NCS_CLK_ENABLE();

    qspi_gpio_handler.Pin       = QSPI_CLK_PIN;
    qspi_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    qspi_gpio_handler.Alternate = QSPI_AF_X;
    qspi_gpio_handler.Pull      = GPIO_PULLUP;
    qspi_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(QSPI_CLK_NCS_PORT, &qspi_gpio_handler);

    qspi_gpio_handler.Pin       = QSPI_IO32_PIN;
    HAL_GPIO_Init(QSPI_IOx_PORT, &qspi_gpio_handler);

    qspi_gpio_handler.Pin       = QSPI_NCS_PIN;
    qspi_gpio_handler.Alternate = QSPI_AF_Y;
    HAL_GPIO_Init(QSPI_CLK_NCS_PORT, &qspi_gpio_handler);

    qspi_gpio_handler.Pin       = QSPI_IO01_PIN;
    HAL_GPIO_Init(QSPI_IOx_PORT, &qspi_gpio_handler);

    qspi_mdma_handler.Instance                      = QSPI_MDMA_CHANNEL;
    qspi_mdma_handler.Init.Priority                 = MDMA_PRIORITY_MEDIUM;
    qspi_mdma_handler.Init.Endianness               = MDMA_LITTLE_ENDIANNESS_PRESERVE;
    qspi_mdma_handler.Init.SourceInc                = MDMA_SRC_INC_BYTE;
    qspi_mdma_handler.Init.SourceBurst              = MDMA_DEST_BURST_4BEATS;
    qspi_mdma_handler.Init.SourceDataSize           = MDMA_SRC_DATASIZE_BYTE;
    qspi_mdma_handler.Init.DestDataSize             = MDMA_DEST_DATASIZE_BYTE;
    qspi_mdma_handler.Init.DataAlignment            = MDMA_DATAALIGN_PACKENABLE;
    qspi_mdma_handler.Init.SourceBlockAddressOffset = 0;
    qspi_mdma_handler.Init.DestBlockAddressOffset   = 0;
    __HAL_LINKDMA(&qspi_init_handler, hmdma, qspi_mdma_handler);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc) {


}

void HAL_SD_MspInit(SD_HandleTypeDef *hsd) {

    if (hsd->Instance == SD) {

        GPIO_InitTypeDef sd_gpio_handler = {0};

        SD_CLK_ENABLE();
        SD_IOx_CLK_ENABLE();
        SD_CMD_CLK_ENABLE();
        SD_CLK_CLK_ENABLE();

        sd_gpio_handler.Pin       = SD_IOx_PIN;
        sd_gpio_handler.Mode      = GPIO_MODE_AF_PP;
        sd_gpio_handler.Alternate = SD_AF;
        sd_gpio_handler.Pull      = GPIO_PULLUP;
        sd_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(SD_IOx_PORT, &sd_gpio_handler);

        sd_gpio_handler.Pin       = SD_CMD_PIN;
        HAL_GPIO_Init(SD_CMD_PORT, &sd_gpio_handler);

        sd_gpio_handler.Pin       = SD_CLK_PIN;
        HAL_GPIO_Init(SD_CLK_PORT, &sd_gpio_handler);
    }
}
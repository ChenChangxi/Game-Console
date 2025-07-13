#include "sys.h"

uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq) {

    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef rcc_osc_init = {0};
    RCC_ClkInitTypeDef rcc_clk_init = {0};

    __HAL_RCC_PWR_CLK_ENABLE();                                     /* 使能PWR时钟 */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  /* 设置调压器输出电压级别 */

    /* 选择HSE为时钟源 */
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rcc_osc_init.HSEState = RCC_HSE_ON;

    /* 配置锁相环 */
    rcc_osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;
    rcc_osc_init.PLL.PLLN = plln;
    rcc_osc_init.PLL.PLLM = pllm;
    rcc_osc_init.PLL.PLLP = pllp;
    rcc_osc_init.PLL.PLLQ = pllq;

    ret = HAL_RCC_OscConfig(&rcc_osc_init);
    if (ret != HAL_OK) {return 1;}

    /* 配置系统/总线时钟 */
    rcc_clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    rcc_clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    ret = HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);
    if (ret != HAL_OK) {return 1;}

    /* 使能FLASH预取功能 */
    if (HAL_GetREVID() == 0x1001) {__HAL_FLASH_PREFETCH_BUFFER_ENABLE();}

    return 0;                    
}
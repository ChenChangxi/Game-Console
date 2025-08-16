#include "sys.h"

RCC_OscInitTypeDef       osc_init;
RCC_ClkInitTypeDef       clk_init;
RCC_PeriphCLKInitTypeDef per_init;

void sys_stm32_clock_init(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq) {

    MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);                          /* 电源更新 */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);   /* 调压等级 */
    while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY);      /* 电压稳定 */

    osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE 
                            | RCC_OSCILLATORTYPE_HSI48
                            | RCC_OSCILLATORTYPE_LSE
                            | RCC_OSCILLATORTYPE_LSI;
    osc_init.HSEState   = RCC_HSE_ON;
    osc_init.HSI48State = RCC_HSI48_ON;               /* 全速USB时钟源 */
    osc_init.HSIState   = RCC_HSI_OFF;
    osc_init.LSEState   = RCC_LSE_ON;                 /* RTC时钟源 */
    osc_init.LSIState   = RCC_LSI_ON;                 /* IWDG时钟源 */
    osc_init.CSIState   = RCC_CSI_OFF;
    osc_init.PLL.PLLState  = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    osc_init.PLL.PLLM      = pllm;
    osc_init.PLL.PLLN      = plln;
    osc_init.PLL.PLLP      = pllp;
    osc_init.PLL.PLLQ      = pllq;
    osc_init.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;         /* 压控振荡器（n倍频后）*/
    osc_init.PLL.PLLRGE    = RCC_PLL1VCIRANGE_0;      /* PLL输入频率 */
    osc_init.PLL.PLLFRACN  = 0;                       /* 小数部分 */
    HAL_RCC_OscConfig(&osc_init);

    clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK
                       | RCC_CLOCKTYPE_HCLK
                       | RCC_CLOCKTYPE_PCLK1
                       | RCC_CLOCKTYPE_PCLK2
                       | RCC_CLOCKTYPE_D1PCLK1
                       | RCC_CLOCKTYPE_D3PCLK1;
    clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clk_init.SYSCLKDivider  = RCC_SYSCLK_DIV1;
    clk_init.AHBCLKDivider  = RCC_HCLK_DIV2;
    clk_init.APB1CLKDivider = RCC_APB1_DIV2;
    clk_init.APB2CLKDivider = RCC_APB2_DIV2;
    clk_init.APB3CLKDivider = RCC_APB3_DIV2;
    clk_init.APB4CLKDivider = RCC_APB4_DIV2;
    HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_4);  /* 由电压和AHB频率决定 */

    per_init.PeriphClockSelection      = RCC_PERIPHCLK_USART16
                                       | RCC_PERIPHCLK_USART234578;                          
    per_init.Usart16ClockSelection     = RCC_USART16CLKSOURCE_D2PCLK2;       /* 16挂载在APB2总线，共用一个选择器 */
    per_init.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;   /* 234578挂载在APB1总线 ，共用一个选择器 */
    HAL_RCCEx_PeriphCLKConfig(&per_init);
}
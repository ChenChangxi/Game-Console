#include "key.h"
#include "timer.h"
#include "usart.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART) {

        if (!(uart_stat & 0x8000)) {

            if (uart_stat & 0x4000) {if (buff == 0x0a) uart_stat |= 0x8000;else uart_stat = 0;}      /* 收到了\n */
            else {

                if (buff == 0x0d) uart_stat |= 0x4000;                                               /* 收到了\r */
                else {data[uart_stat++] = buff;if (uart_stat >= USART_DATA_SIZE) uart_stat = 0;}  /* 到这里前两位为0 */
            }
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

    delay_ms(20);      /* 消抖 */

    switch (GPIO_Pin) {

        case KEY0_EXTI_Pin : {do {LED0(0);LED1(1);delay_ms(500);} while (!KEY0);break;}
        
        case KEY1_EXTI_Pin : {do {LED0(1);LED1(0);delay_ms(500);} while (!KEY1);break;}
            
        case KEY2_EXTI_Pin : {do {LED0(1);LED1(0);delay_ms(500);} while (!KEY2);break;}
    }
}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg) {if (hwwdg->Instance == WWDG) wwdg_feed();}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == LED_TIME) {LED0_TOGGLE();LED1_TOGGLE();}
    else if (htim->Instance == WDG_TIME) {iwdg_feed();wwdg_feed();}
    else if (htim->Instance == BLN_TIME) {

        __HAL_TIM_SET_COMPARE(&bln_time_handler, BLN_TIME_PWM_CHANNEL, get_pers(400, &ins));           /* 改变占空比 */
        __HAL_TIM_SET_COMPARE(&bln_time_handler, BLN_TIME_PHASEX_CHANNEL, get_pers(400, &cnx));        /* 改变相位值 */
        __HAL_TIM_SET_COMPARE(&bln_time_handler, BLN_TIME_PHASEY_CHANNEL, get_pers(400, &cny) + 500);  /* 改变相位值（50%初相）*/

    } else if (htim->Instance == KIC_TIME) {

        if (!(time_stat & 0x8000) && (time_stat & 0x4000)) {  /* 未准备发送且来了上升沿 */

            if ((time_stat & 0x3fff) != 0x3fff) time_stat++;  /* 周期数达到最大值 */
            else {

                time_stat |= 0x8000;
                time_coun = 0xffff;
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除下降沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_RISING);    /* 改为上升沿触发 */
            }
        }
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == BLN_TIME) {

        GPIO_PinState x = HAL_GPIO_ReadPin(BLN_TIME_PORT, BLN_TIME_PHASEX_PIN);
        GPIO_PinState y = HAL_GPIO_ReadPin(BLN_TIME_PORT, BLN_TIME_PHASEY_PIN);
        HAL_GPIO_WritePin(BLN_TIME_PORT, BLN_TIME_PHASE_PIN, (x ^ y) ? GPIO_PIN_SET : GPIO_PIN_RESET);  /* 调制波形信号 */
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == KIC_TIME) {

        if (!(time_stat & 0x8000)) {

            if (!(time_stat & 0x4000)) {                      /* 来了上升沿 */

                time_stat |= 0x4000;
                __HAL_TIM_DISABLE(&kic_time_handler);         /* 关闭定时器 */
                __HAL_TIM_SET_COUNTER(&kic_time_handler, 0);  /* 计数器清零 */
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除上升沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_FALLING);   /* 改为下降沿触发 */
                __HAL_TIM_ENABLE(&kic_time_handler);          /* 打开定时器 */

            } else {                                          /* 来了下降沿 */

                time_stat |= 0x8000;
                time_coun = HAL_TIM_ReadCapturedValue(&kic_time_handler, KIC_TIME_CHANNEL);             /* 读取计数器的值 */
                TIM_RESET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL);                         /* 清除下降沿触发 */
                TIM_SET_CAPTUREPOLARITY(&kic_time_handler, KIC_TIME_CHANNEL, TIM_ICPOLARITY_RISING);    /* 改为上升沿触发 */
            }
        }
    }
}
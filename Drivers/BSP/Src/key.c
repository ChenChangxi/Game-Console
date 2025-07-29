#include "key.h"

void key_init(void) {

    GPIO_InitTypeDef key_init;

    KEY0_EXTI_CLK_ENABLE();
    KEY1_EXTI_CLK_ENABLE();
    KEY2_EXTI_CLK_ENABLE();
    KEYU_EXTI_CLK_ENABLE();

    /* 配置了GPIO，SYSCLG，EXTI */
    key_init.Pin   = KEY0_EXTI_Pin;
    key_init.Mode  = GPIO_MODE_IT_FALLING;
    key_init.Pull  = GPIO_PULLUP;
    key_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY0_EXTI_PORT, &key_init);

    /* 配置NVIC */
    HAL_NVIC_SetPriority(KEY0_EXTI_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);

    key_init.Pin   = KEY1_EXTI_Pin;
    HAL_GPIO_Init(KEY1_EXTI_PORT, &key_init);
    HAL_NVIC_SetPriority(KEY1_EXTI_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(KEY1_EXTI_IRQn);

    key_init.Pin   = KEY2_EXTI_Pin;
    HAL_GPIO_Init(KEY2_EXTI_PORT, &key_init);
    HAL_NVIC_SetPriority(KEY2_EXTI_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(KEY2_EXTI_IRQn);

    key_init.Pin  = KEYU_EXTI_Pin;
    key_init.Mode = GPIO_MODE_IT_RISING;
    key_init.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEYU_EXTI_PORT, &key_init);
    HAL_NVIC_SetPriority(KEYU_EXTI_IRQn, 3, 2);
    HAL_NVIC_EnableIRQ(KEYU_EXTI_IRQn);
}

void KEY0_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY0_EXTI_Pin);}

void KEY1_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY1_EXTI_Pin);}

void KEY2_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY2_EXTI_Pin);}

void KEYU_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEYU_EXTI_Pin);}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

    delay_ms(20);      /* 消抖 */

    switch (GPIO_Pin) {

        case KEY0_EXTI_Pin : {do {LED0(0);LED1(1);BEEP(0);} while (!KEY0);break;}
        
        case KEY1_EXTI_Pin : {do {LED0(1);LED1(0);BEEP(0);} while (!KEY1);break;}
            
        case KEY2_EXTI_Pin : {do {LED0(1);LED1(1);BEEP(1);} while (!KEY2);break;}

        case KEYU_EXTI_Pin : {

            do {
                HAL_UART_Transmit(&uart_handler, exti, USART_UX_EXTI_SIZE, 1000);
                while (__HAL_UART_GET_FLAG(&uart_handler, UART_FLAG_TC) != SET);
                LED0(1);LED1(1);BEEP(0);delay_ms(1000);
            } while (KEYU);break;
        }
    }
}

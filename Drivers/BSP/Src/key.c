#include "key.h"

GPIO_InitTypeDef key_handler;
uint8_t exti[USART_UX_EXTI_SIZE] = 
    {0xE4, 0xBD, 0xA0, 0xE5, 0xA5, 0xBD, 0x53, 0x54, 0x4D, 0x33, 0x32, 0x0D, 0x0A};

void key_init(void) {

    KEY0_EXTI_CLK_ENABLE();
    KEY1_EXTI_CLK_ENABLE();
    KEY2_EXTI_CLK_ENABLE();
    KEYU_EXTI_CLK_ENABLE();

    /* 配置了GPIO，SYSCLG，EXTI */
    key_handler.Pin   = KEY0_EXTI_Pin;
    key_handler.Mode  = GPIO_MODE_IT_FALLING;
    key_handler.Pull  = GPIO_PULLUP;
    key_handler.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY0_EXTI_PORT, &key_handler);

    /* 配置NVIC */
    HAL_NVIC_SetPriority(KEY0_EXTI_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);

    key_handler.Pin   = KEY1_EXTI_Pin;
    HAL_GPIO_Init(KEY1_EXTI_PORT, &key_handler);
    HAL_NVIC_SetPriority(KEY1_EXTI_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(KEY1_EXTI_IRQn);

    key_handler.Pin   = KEY2_EXTI_Pin;
    HAL_GPIO_Init(KEY2_EXTI_PORT, &key_handler);
    HAL_NVIC_SetPriority(KEY2_EXTI_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(KEY2_EXTI_IRQn);

    key_handler.Pin  = KEYU_EXTI_Pin;
    key_handler.Mode = GPIO_MODE_IT_RISING;
    key_handler.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEYU_EXTI_PORT, &key_handler);
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

        case KEY0_EXTI_Pin : {do {LED0(0);LED1(1);} while (!KEY0);break;}
        
        case KEY1_EXTI_Pin : {do {LED0(1);LED1(0);} while (!KEY1);break;}
            
        case KEY2_EXTI_Pin : {do {LED0(1);LED1(1);} while (!KEY2);break;}

        case KEYU_EXTI_Pin : {

            do {LED0(1);LED1(1);delay_ms(1000);usart_transmit(exti, USART_UX_EXTI_SIZE);} while (KEYU);break;
        }
    }
}

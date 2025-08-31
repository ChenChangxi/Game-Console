#include "key.h"

GPIO_InitTypeDef key_handler;

void key_init(void) {

    KEY0_EXTI_CLK_ENABLE();
    KEY1_EXTI_CLK_ENABLE();
    KEY2_EXTI_CLK_ENABLE();

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
}

void KEY0_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY0_EXTI_Pin);}

void KEY1_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY1_EXTI_Pin);}

void KEY2_EXTI_IRQHandler(void) {HAL_GPIO_EXTI_IRQHandler(KEY2_EXTI_Pin);}
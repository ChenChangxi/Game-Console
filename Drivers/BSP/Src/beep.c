#include "beep.h"

void beep_init(void) {

    GPIO_InitTypeDef gpio_init;

    BEEP_GPIO_CLK_ENABLE();

    gpio_init.Pin   = BEEP_GPIO_PIN;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull  = GPIO_PULLDOWN;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init);

    /* NPN三极管高电平导通 */
    BEEP(0);
}
#include "fmc.h"

void fmc_init(void) {

    GPIO_InitTypeDef fmc_gpio_handler = {0};

    FMC_CLK_ENABLE();
    FMC_DATA_X_CLK_ENABLE();
    FMC_DATA_Y_CLK_ENABLE();
    FMC_ADDR_X_CLK_ENABLE();
    FMC_ADDR_Y_CLK_ENABLE();

    fmc_gpio_handler.Pin       = FMC_DATA_PIN_X;
    fmc_gpio_handler.Mode      = GPIO_MODE_AF_PP;
    fmc_gpio_handler.Alternate = FMC_AF;
    fmc_gpio_handler.Pull      = GPIO_PULLUP;
    fmc_gpio_handler.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(FMC_DATA_PORT_X, &fmc_gpio_handler);

    fmc_gpio_handler.Pin       = FMC_DATA_PIN_Y;
    HAL_GPIO_Init(FMC_DATA_PORT_Y, &fmc_gpio_handler);

    fmc_gpio_handler.Pin       = FMC_ADDR_PIN_X;
    HAL_GPIO_Init(FMC_ADDR_PORT_X, &fmc_gpio_handler);

    fmc_gpio_handler.Pin       = FMC_ADDR_PIN_Y;
    HAL_GPIO_Init(FMC_ADDR_PORT_Y, &fmc_gpio_handler);
}
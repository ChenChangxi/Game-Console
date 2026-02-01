#include "sd.h"

SD_HandleTypeDef sd_init_handler;

void sd_init(void) {

    HAL_SD_Init(&sd_init_handler);
}
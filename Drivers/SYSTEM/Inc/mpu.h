/* 内存保护 */

#ifndef __MPU_H
#define __MPU_H

#include "sys.h"

/* 区域保护 */
void mpu_set(uint8_t num, uint32_t bas, uint8_t siz, uint8_t exe,
             uint8_t acc, uint8_t tex,  uint8_t cae, uint8_t buf, uint8_t sha);

/* 内存保护 */
void memory_protect(void);

/* 变量声明 */
extern MPU_Region_InitTypeDef mpu_set_handler;

#endif
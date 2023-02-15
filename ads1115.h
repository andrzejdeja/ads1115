/*
 * STM32 HAL driver for ADS1115
 * Configured for STM32F4 running FreeRTOS/CMSISv1
 * 
 *   @file     ads1115.h
 *   @author   A. Deja
 */

#ifndef __ADS1115_H__
#define __ADS1115_H__

#include <stddef.h>
#include <_ansi.h>

_BEGIN_STD_C

#include "ads1115_conf.h"

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#endif


//void ads1115_Init(void); //Init was not needed as startup values were correct for the intended purpose

HAL_StatusTypeDef ads1115_Reset(void);

HAL_StatusTypeDef ads1115_SwitchMUXPGA(uint8_t mux, uint8_t pga);

uint8_t ads1115_GetValue(uint8_t * data, uint8_t mux, uint8_t pga);

_END_STD_C

#endif // __ADS1115_H__

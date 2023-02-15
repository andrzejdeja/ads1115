/*
 * STM32 HAL driver for ADS1115
 * Configured for STM32F4 running FreeRTOS/CMSISv1
 * 
 *   @file     ads1115.c
 *   @author   A. Deja
 */

#include "ads1115.h"
#include "i2c.h"

#include <stdlib.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"


/*
void ads1115_Init(void) {
	return;
}
*/

HAL_StatusTypeDef ads1115_Reset(void) {
	uint8_t byte[3];
	byte[0] = 0x01; //Pointer for config register
	byte[1] = (uint8_t)((ADS1115_OS_CONF << ADS1115_OS_SHIFT_8)
			| (ADS1115_MUX_0_1 << ADS1115_MUX_SHIFT_8)
			| (ADS1115_PGA_2V << ADS1115_PGA_SHIFT_8)
			| (ADS1115_MODE_SS << ADS1115_MODE_SHIFT_8)); //D15:D8
	byte[2] = (uint8_t)((ADS1115_DR_DEFAULT << ADS1115_DR_SHIFT)
			| (ADS1115_COMP_ALL << ADS1115_COMP_ALL_SHIFT));
	return HAL_I2C_Master_Transmit(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, byte, 3, HAL_MAX_DELAY);
}

HAL_StatusTypeDef ads1115_SwitchMUXPGA(uint8_t mux, uint8_t pga)
{
	uint8_t byte[3];
	byte[0] = 0x01; //Pointer for config register
	byte[1] = (uint8_t)((ADS1115_OS_CONF << ADS1115_OS_SHIFT_8)
			| (mux << ADS1115_MUX_SHIFT_8)
			| (pga << ADS1115_PGA_SHIFT_8)
			| (ADS1115_MODE_SS << ADS1115_MODE_SHIFT_8)); //D15:D8
	byte[2] = (uint8_t)((ADS1115_DR_DEFAULT << ADS1115_DR_SHIFT)
			| (ADS1115_COMP_ALL << ADS1115_COMP_ALL_SHIFT));
	return HAL_I2C_Master_Transmit(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, byte, 3, HAL_MAX_DELAY);
}

//HAL write functions add READ bit by themselves

uint8_t ads1115_GetValue(uint8_t * data, uint8_t mux, uint8_t pga)
{
	uint8_t byte[3];
	byte[0] = 0x01; //Pointer for config register
	byte[1] = (uint8_t)((ADS1115_OS_START << ADS1115_OS_SHIFT_8)
			| (mux << ADS1115_MUX_SHIFT_8)
			| (pga << ADS1115_PGA_SHIFT_8)
			| (ADS1115_MODE_SS << ADS1115_MODE_SHIFT_8)); //D15:D8
	byte[2] = (uint8_t)((ADS1115_DR_DEFAULT << ADS1115_DR_SHIFT)
			| (ADS1115_COMP_ALL << ADS1115_COMP_ALL_SHIFT));
	uint8_t res;
	//Set pointer to config
	taskENTER_CRITICAL();
	res = HAL_I2C_Master_Transmit(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, byte, 3, HAL_MAX_DELAY); //Set pointer to config reg and start conv
	taskEXIT_CRITICAL();
	if(res != HAL_OK)
	{
		return res;
	}
	osDelay(1);
	while (1)
	{
		//Read config register
		taskENTER_CRITICAL();
		res = HAL_I2C_Master_Receive(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, data, 2, HAL_MAX_DELAY);
		taskEXIT_CRITICAL();
		if(res != HAL_OK)
		{
			return res;
		}
		if ((data[0] & 0x80) == 0x80) //Has conv stopped?
		{
			break;
		}
	}
	osDelay(1);
	//Set pointer to conv
	byte[0] = 0x00;
	taskENTER_CRITICAL();
	res = HAL_I2C_Master_Transmit(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, byte, 1, HAL_MAX_DELAY);
	taskEXIT_CRITICAL();
	if(res != HAL_OK)
	{
		return res;
	}
	osDelay(1);
	//Read conv register
	taskENTER_CRITICAL();
	res = HAL_I2C_Master_Receive(&ADS1115_I2C_PORT, ADS1115_I2C_ADDR, data, 2, HAL_MAX_DELAY);
	taskEXIT_CRITICAL();
	return res;
}

#ifndef __ADS1115_CONF_H__
#define __ADS1115_CONF_H__

// Choose a microcontroller family
#define STM32F4

//0x48 = 01001000 - ADDR pin to GND via 1k resistor

// I2C Configuration
#define ADS1115_I2C_PORT        hi2c2
#define ADS1115_I2C_ADDR        (0x48 << 1)

/*
 * Address Pointer Register P[1:0]
 * 00 : Conversion register
 * 01 : Config register
 * 10 : Lo_thresh register
 * 11 : Hi_thresh register
 *
 * reset = 00h
 */

/*
 *  Conversion Register
 *  16-bit read only
 *  reset = 0000h
 */

/*
 * Config Register
 *
 * Bit		Field			Reset
 * 15 		OS				1h
 * 14:12 	MUX[2:0]		0h
 * 11:9		PGA[2:0] 		2h
 * 8 		MODE 			1h
 * 7:5 		DR[2:0]			4h
 * 4 		COMP_MODE		0h
 * 3 		COMP_POL 		0h
 * 2 		COMP_LAT		0h
 * 1:0 		COMP_QUE[1:0]	3h
 *
 */

#define ADS1115_OS_CONF 0x00
#define ADS1115_OS_START 0x01

#define ADS1115_MUX_0_1 0x00
#define ADS1115_MUX_2_3 0x03
#define ADS1115_MUX_0_GND 0x04
#define ADS1115_MUX_2_GND 0x06

#define ADS1115_PGA_4V 0x01
#define ADS1115_PGA_2V 0x02
#define ADS1115_PGA_1V 0x03
#define ADS1115_PGA_0V5 0x04
#define ADS1115_PGA_0V25 0x05

#define ADS1115_MODE_SS 0x01 //Single-shot
#define ADS1115_MODE_C 0x00 //Cont

#define ADS1115_DR_DEFAULT 0x04 //SPS

#define ADS1115_COMP_MODE 0x00 //not used

#define ADS1115_COMP_POL 0x00 //not used

#define ADS1115_COMP_LAT 0x00 //not used

#define ADS1115_COMP_QUE 0x03 //not used (0x03)

#define ADS1115_OS_SHIFT 15
#define ADS1115_MUX_SHIFT 12
#define ADS1115_PGA_SHIFT 9
#define ADS1115_MODE_SHIFT 8

#define ADS1115_OS_SHIFT_8 7
#define ADS1115_MUX_SHIFT_8 4
#define ADS1115_PGA_SHIFT_8 1
#define ADS1115_MODE_SHIFT_8 0

#define ADS1115_DR_SHIFT 5
#define ADS1115_COMP_MODE_SHIFT 4
#define ADS1115_COMP_POL_SHIFT 3
#define ADS1115_COMP_LAT_SHIFT 2
#define ADS1115_COMP_QUE_SHIFT 0

//When not using comp we can combine its config:
//4:0

#define ADS1115_COMP_ALL 0x03
#define ADS1115_COMP_ALL_SHIFT 0

#endif /* __ADS1115_CONF_H__ */

/*
 * sct.h
 *
 *  Created on: Oct 8, 2025
 *      Author: Mara
 */

#ifndef INC_SCT_H_
#define INC_SCT_H_

#include "main.h"

// Pinout SCT_NOE_Pin | SCT_CLK_Pin | SCT_SDI_Pin | SCT_NLA_Pin
// Sense on rising edge of clock

#define SET_CLK() HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1)
#define RESET_CLK() HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0)

#define SET_SDI() HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, 1)
#define RESET_SDI() HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, 0)

#define PULSE_LA() HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1); HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0)

#define ENABLE_OUTPUT() HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0)



void sct_init(void);
void sct_led(uint32_t value);
void sct_value(uint16_t value);

static const uint32_t reg_values[3][10] = {
		{
				//PCDE--------GFAB @ DIS1
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
		},
		{
				//----PCDEGFAB---- @ DIS2
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
		},
		{
				//PCDE--------GFAB @ DIS3
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
		},
};


#endif /* INC_SCT_H_ */

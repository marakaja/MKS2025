#include <stdint.h>
#include "sct.h"

void sct_init()
{
	ENABLE_OUTPUT();
}

void sct_led(uint32_t value)
{
	for(uint8_t i = 0; i < 32; i++)
	{
		RESET_CLK();
		if(value & 0b1)
		{
			SET_SDI();
		}
		else
		{
			RESET_SDI();
		}

		SET_CLK();
		value = value >> 1;
	}

	PULSE_LA();
}

void sct_value(uint16_t value)
{
	uint32_t reg = 0;

	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10 % 10];
	reg |= reg_values[2][value / 1 % 10];

	sct_led(reg);
}

#include "main.h"

#include "sct.h"


#define SET_CLK() HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1)
#define RESET_CLK() HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0)

#define SET_SDI() HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, 1)
#define RESET_SDI() HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, 0)

#define PULSE_LA() do  {HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1); HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);} while (0)

#define ENABLE_OUTPUT() HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0)


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

const uint32_t LED_MASKS[8] = {
    (1 << 8), // LED1  → bit9
    (1 << 9), // LED2  → bit10
    (1 << 10), // LED3  → bit11
    (1 << 11), // LED4  → bit12
    (1 << 7), // LED5  → bit8
    (1 << 6), // LED6  → bit7
    (1 << 5), // LED7  → bit6
    (1 << 4)  // LED8  → bit5
};

uint32_t get_bar_mask(uint8_t level)
{
    uint32_t mask = 0;
    for (uint8_t i = 0; i < level && i < 8; i++)
        mask |= LED_MASKS[i]<<16;
    return mask;
}

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

void sct_value(uint16_t value, uint8_t led, uint8_t dot)
{
	uint32_t reg = 0;
	led =  (led>8)?8:led;

	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10 % 10];
	reg |= reg_values[2][value / 1 % 10];
	reg |= get_bar_mask(led);
	reg |= (dot==1)?(1<<(16)):0;
	reg |= (dot==2)?(0b0000100000000000):0;
	reg |= (dot==3)?(1<<(0)):0;

	sct_led(reg);
}

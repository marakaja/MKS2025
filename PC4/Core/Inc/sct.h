/*
 * sct.h
 *
 *  Created on: Oct 8, 2025
 *      Author: Mara
 */

#ifndef INC_SCT_H_
#define INC_SCT_H_

#include <stdint.h>

// Pinout SCT_NOE_Pin | SCT_CLK_Pin | SCT_SDI_Pin | SCT_NLA_Pin
// Sense on rising edge of clock

void sct_init(void);
void sct_led(uint32_t value);
uint32_t get_bar_mask(uint8_t level);
void sct_value(uint16_t value, uint8_t led, uint8_t dot);

#endif /* INC_SCT_H_ */

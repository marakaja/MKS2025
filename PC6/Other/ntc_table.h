#ifndef NTC_TABLE_H
#define NTC_TABLE_H

#include <stdint.h>

// Lookup table for NTC temperature sensor
// Each value = temperature * 100 (e.g., 2534 = 25.34 °C)
extern const int16_t ntc_table[1024];

#endif // NTC_TABLE_H

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# === Konfigurace ===
R_FIXED = 10000.0     # referenční odpor v ohmech
ADC_RES = 1023        # 10bit ADC
INPUT_FILE = "ntc.csv"
C_FILE = "ntc_table.c"
H_FILE = "ntc_table.h"

# === Načtení dat ===
data = pd.read_csv(INPUT_FILE)
data.columns = ["Temperature_C", "Resistance_norOhm"]
data["Resistance_Ohm"] = data["Resistance_norOhm"] * 1000

# === Přepočet odporu na ADC hodnotu ===
# Schéma: VREF -> NTC -> ADC -> 1k -> GND
# Vout = Vref * R_FIXED / (R_NTC + R_FIXED)
data["ADC"] = ADC_RES * (data["Resistance_Ohm"] / (data["Resistance_Ohm"] + R_FIXED))
data["ADC"] = data["ADC"].round().astype(int)
data = data.drop_duplicates(subset="ADC").sort_values("ADC")

# save as CSV for reference, use ; as separator
data.to_csv("ntc_converted.csv", index=False, sep=';')

# === Interpolace teplot pro 0–1023 ===
adc_values = np.arange(0, ADC_RES + 1)
plt.plot(data["ADC"], data["Temperature_C"], 'x', label='Data points')
temps = np.interp(adc_values, data["ADC"], data["Temperature_C"])
plt.plot(adc_values, temps, '-', label='Interpolated')
plt.xlabel("ADC Value")
plt.ylabel("Temperature (°C)")
plt.legend()
plt.grid()
plt.show()

# === Převod na fixed-point formát (×100) ===
temps_fixed = np.round(temps * 100).astype(int)

# === Vygenerování obsahu C souboru ===
array_lines = []
for i in range(0, len(temps_fixed), 16):
    chunk = ", ".join(f"{t:6d}" for t in temps_fixed[i:i+16])
    array_lines.append(f"    {chunk},")

c_content = f"""#include "ntc_table.h"

const int16_t ntc_table[1024] = {{
{chr(10).join(array_lines)}
}};
"""

h_content = """#ifndef NTC_TABLE_H
#define NTC_TABLE_H

#include <stdint.h>

// Lookup table for NTC temperature sensor
// Each value = temperature * 100 (e.g., 2534 = 25.34 °C)
extern const int16_t ntc_table[1024];

#endif // NTC_TABLE_H
"""

# === Uložení souborů ===
with open(C_FILE, "w", encoding="utf-8") as f:
    f.write(c_content)
with open(H_FILE, "w", encoding="utf-8") as f:
    f.write(h_content)

print("✅ Lookup table generated for NTC-on-top configuration")

#include "dstemperature.h"

uint8_t DallasTemp_ReadScratchpad(uint8_t *scratchpad) {
  OneWire_SkipROM();
  OneWire_WriteByte(DS18B20_CMD_RSCRATCHPAD);
  
  for (uint8_t i = 0; i < 8; i++) {
    scratchpad[i] = OneWire_ReadByte();
  }
  
  uint8_t calculated_crc = OneWire_CRC8_Update(scratchpad, 8);
  uint8_t crc = OneWire_ReadByte();
  
  if (calculated_crc != crc) return 0;
  
  return 1;
}

uint8_t DallasTemp_Convert(void) {
  if (!OneWire_Presence()) return 0;
  OneWire_WriteByte(ONE_WIRE_SKIPROM);
  OneWire_WriteByte(DS18B20_CMD_CONVERTTEMP);
  return 1;
}

void DallasTemp_GetTemperature(DallasSensor *Sensor) {
  if (!DallasTemp_Convert()) return;
  _delay_ms(750);
  if (!DallasTemp_ReadScratchpad(Sensor->SCRATCHPAD)) return;
  Sensor->TEMPERATURE = ((Sensor->SCRATCHPAD[1] << 8) | Sensor->SCRATCHPAD[0]) / 16;
  Sensor->TEMPERATURE_FRACTION = ((Sensor->SCRATCHPAD[0] & 0x0f) * 100) / 16;
}
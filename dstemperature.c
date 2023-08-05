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

// TODO parasite power
uint8_t DallasTemp_CopyScratchpad(void) {
  if (!OneWire_Presence()) return 0;
  OneWire_SkipROM();
  OneWire_WriteByte(DS18B20_CMD_CPSCRATCHPAD);
  _delay_ms(10);
  return 1;
}

void DallasTemp_WriteScratchpad(uint8_t *data) {
  uint8_t i = 3;
  
  OneWire_SkipROM();
  OneWire_WriteByte(DS18B20_CMD_WSCRATCHPAD);
  
  do {
    OneWire_WriteByte(*data++);
  } while (--i);
  
  DallasTemp_CopyScratchpad();
}

void DallasTemp_SetResolution(DallasSensor *Sensor, uint8_t r) {
  DallasTemp_ReadScratchpad(Sensor->SCRATCHPAD);
  
  uint8_t data[3] = { Sensor->SCRATCHPAD[2], Sensor->SCRATCHPAD[3], 0x7f };
  
  switch(r) {
    case 12:
      data[2] = 0x7f;
      break;
    case 11:
      data[2] = 0x5f;
      break;
    case 10:
      data[2] = 0x3f;
      break;
    case 9:
      data[2] = 0x1f;
      break;
    default:
      data[2] = 0x7f;
      break;
  }
  
  DallasTemp_WriteScratchpad(data);
}

uint8_t DallasTemp_Convert(void) {
  if (!OneWire_Presence()) return 0;
  OneWire_WriteByte(ONE_WIRE_SKIPROM);
  OneWire_WriteByte(DS18B20_CMD_CONVERTTEMP);
  return 1;
}

uint8_t DallasTemp_CheckError(DallasSensor* Sensor) {
  if (!OneWire_Presence()) return 1;
  OneWire_ReadROM(Sensor->ROM);
  if (Sensor->ROM[0] != DS18B20_CONST_FAMILY_CODE) return 1;
  return 0;
}

void DallasTemp_GetTemperature(DallasSensor *Sensor) {
  if (!DallasTemp_Convert()) return;
  
  if (!(~Sensor->SCRATCHPAD[4] & 0x60)) {
    _delay_ms(750);
  } else if (!(~Sensor->SCRATCHPAD[4] & 0x40)) {
    _delay_ms(375);
  } else if (!(~Sensor->SCRATCHPAD[4] & 0x20)) {
    _delay_ms(188);
  } else {
    _delay_ms(94);
  }
  
  if (!DallasTemp_ReadScratchpad(Sensor->SCRATCHPAD)) return;
  Sensor->TEMPERATURE = ((Sensor->SCRATCHPAD[1] << 8) | Sensor->SCRATCHPAD[0]) / 16;
  
  /* 
   * Двойное дополнение для дробной части если минусовая температура:
   * проверяем что последние пять битов в старшем байте температуры стоят в единице
   */
  if (!(~Sensor->SCRATCHPAD[1] & 0xf8)) {
    Sensor->T_NEGATIVE = 1;
    Sensor->SCRATCHPAD[0] = -Sensor->SCRATCHPAD[0];
  } else {
    Sensor->T_NEGATIVE = 0;
  }
  
  /**
   * Получаем дробную часть через битовую маску 0x0f, умножаем для получения точности.
   */
  Sensor->TEMPERATURE_FRACTION = ((Sensor->SCRATCHPAD[0] & 0x0f) * 1000) / 16;
}

//float DallasTemp_GetFloatTemperature(DallasSensor *Sensor) {
//  DallasTemp_GetTemperature(Sensor);
//  return (float)((float)Sensor->TEMPERATURE + ((float)Sensor->TEMPERATURE_FRACTION / 1000));
//}
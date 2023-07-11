#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "onewire.h"

#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe

typedef struct DallasSensor {
  uint8_t SCRATCHPAD[8];            // ОЗУ
  uint8_t ROM[8];                   // ПЗУ
  int16_t TEMPERATURE;              // Температура в градусах цельсия (целая часть)
  uint8_t TEMPERATURE_FRACTION;     // Дробная часть
} DallasSensor;

/**
 * Читает ОЗУ датчика
 * @param scratchpad - первые 8 байт.
 * @return "1" - если данные успешно прочитались, "0" - если данные искажены
 */
uint8_t DallasTemp_ReadScratchpad(uint8_t *scratchpad) {
  OneWire_SkipROM();
  OneWire_WriteByte(DS18B20_CMD_RSCRATCHPAD);
  
  for (uint8_t i = 0; i < 8; i++) {
    scratchpad[i] = OneWire_ReadByte();
  }
  
  uint8_t calculated_crc = OneWire_CRC8_Update(scratchpad, 8);
  uint8_t crc = OneWire_ReadByte();
  
  if (calculated_crc != crc) return 0;
  
  asm("nop");
  
  return 1;
}

/**
 * Отправляет команду для оцифровки температуры.
 * @return "1" - если команда отправлена, "0" - если не было ответа от датчика
 */
uint8_t DallasTemp_Convert() {
  if (!OneWire_Presence()) return 0;
  OneWire_WriteByte(ONE_WIRE_SKIPROM);
  OneWire_WriteByte(DS18B20_CMD_CONVERTTEMP);
  return 1;
}

/**
 * Получает оцифрованное значение датчика и конвертирует занчение в читаемый вид.
 * @param Sensor - структура датчика
 */
void DallasTemp_GetTemperature(DallasSensor *Sensor) {
  if (!DallasTemp_Convert()) return;
  _delay_ms(750);
  if (!DallasTemp_ReadScratchpad(Sensor->SCRATCHPAD)) return;
  Sensor->TEMPERATURE = ((Sensor->SCRATCHPAD[1] << 8) | Sensor->SCRATCHPAD[0]) / 16;
  Sensor->TEMPERATURE_FRACTION = ((Sensor->SCRATCHPAD[0] & 0x0f) * 100) / 16;
}

void MCU_Init(void) {
  DDRB = _BV(PB1) | _BV(PB2);
  PORTB = 0x00;
}

int main(void) {
  MCU_Init();
  
  DallasSensor Sensor_01;
  
  while (1) {
    OneWire_ReadROM(Sensor_01.ROM);
    DallasTemp_GetTemperature(&Sensor_01);
    asm("nop");
  }
  return 0;
}
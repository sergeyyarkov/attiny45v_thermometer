#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "onewire.h"

#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe

uint8_t dallas_scratchpad[9] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t dallas_rom[8] = { 0, 0, 0, 0, 0, 0, 0, 0, };

uint8_t DallasTemp_ReadScratchpad() {
  uint8_t i = 0;
  
  OneWire_SkipROM();
  OneWire_WriteByte(DS18B20_CMD_RSCRATCHPAD);
  
  
  while (i < 9) {
    dallas_scratchpad[i++] = OneWire_ReadByte();
  }
  
  return 1;
}

uint8_t DallasTemp_Convert() {
  if (!OneWire_Presence()) return 0;
  OneWire_WriteByte(ONE_WIRE_SKIPROM);
  OneWire_WriteByte(DS18B20_CMD_CONVERTTEMP);
  return 1;
}

void DallasTemp_GetTemperature(int8_t *data, uint8_t *fraction) {
  DallasTemp_Convert();
  _delay_ms(750);
  DallasTemp_ReadScratchpad();
  
  (*data) = ((dallas_scratchpad[1] << 8) | dallas_scratchpad[0]) / 16;
  (*fraction) = ((dallas_scratchpad[0] & 0x0f) * 100) / 16;
}

void MCU_Init(void) {
  DDRB = _BV(PB1) | _BV(PB2);
  PORTB = 0x00;
}

int main(void) {
  MCU_Init();
  
  int8_t temperature = 0;
  uint8_t fraction = 0;
  
  OneWire_ReadROM(dallas_rom);

  while (1) {
    DallasTemp_GetTemperature(&temperature, &fraction);
    asm("nop");
  }
  return 0;
}
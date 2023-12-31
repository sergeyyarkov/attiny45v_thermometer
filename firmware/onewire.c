#include "onewire.h"

uint8_t OneWire_Presence(void) {
  uint8_t is_detected = 0;
  
  cli();
  ow_pull();
  _delay_us(480);
  ow_release();
  _delay_us(70);
  if (bit_is_clear(OW_PIN, OW_LINE)) is_detected = 1;
  _delay_us(410);
  sei();
  return is_detected;
}

void OneWire_WriteByte(uint8_t byte) {
  uint8_t i = 8;

  do {
    cli();
    if (byte & 0x01) {
      ow_pull();
      _delay_us(6);
      ow_release();
      _delay_us(64);
    } else {
      ow_pull();
      _delay_us(60);
      ow_release();
      _delay_us(10);
    }
    sei();
    byte >>= 1;
  } while (--i);
}

uint8_t OneWire_ReadByte() {
  uint8_t byte = 0;
  uint8_t i = 8;
  
  do {
    cli();
    byte >>= 1;
    ow_pull();
    _delay_us(6);
    ow_release();
    _delay_us(9);
    if (bit_is_set(OW_PIN, OW_LINE)) byte |= (1<<7);
    _delay_us(55);
    sei();
  } while (--i);

  return byte;
}

uint8_t OneWire_SkipROM() {
  if (!OneWire_Presence()) return 0;
  OneWire_WriteByte(ONE_WIRE_SKIPROM);
  return 1;
}

uint8_t OneWire_ReadROM(uint8_t *buffer) {
  if (!OneWire_Presence()) return 0;
  
  uint8_t i = 8;
  OneWire_WriteByte(ONE_WIRE_READROM);
  
  do {
    *(buffer++) = OneWire_ReadByte();
  } while (--i);
  
  return 1;
}

uint8_t OneWire_CRC8_Update(uint8_t *buffer, size_t len) {
  uint8_t crc = 0;
  
  do {
    uint8_t i = 8;
    crc ^= *(buffer++);
    do {
      if (crc & 0x01) {
        crc = (crc >> 1) ^ 0x8c;
      } else {
        crc >>= 1;
      }
    } while (--i);
  } while (--len);
  return crc;
}
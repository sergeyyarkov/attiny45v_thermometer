#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define OW_LINE PB0
#define OW_PIN  PINB
#define OW_PORT PORTB
#define OW_DDR  DDRB

#define ow_pull()     (OW_DDR = _BV(OW_LINE))
#define ow_release()  (OW_DDR = !_BV(OW_LINE))

#define ONE_WIRE_READROM    0x33
#define ONE_WIRE_SKIPROM    0xcc
#define ONE_WIRE_SEARCHROM  0xf0
#define ONE_WIRE_MATCHROM   0x55

#ifndef ONEWIRE_H
#define	ONEWIRE_H

uint8_t OneWire_Presence(void);
void OneWire_WriteByte(uint8_t byte);
uint8_t OneWire_ReadByte();
uint8_t OneWire_SkipROM();
uint8_t OneWire_ReadROM(uint8_t *buffer);

#endif	/* ONEWIRE_H */


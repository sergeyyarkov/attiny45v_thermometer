#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define OW_LINE PB4
#define OW_PIN  PINB
#define OW_PORT PORTB
#define OW_DDR  DDRB

#define ow_pull()     (OW_DDR |= _BV(OW_LINE))
#define ow_release()  (OW_DDR &= ~_BV(OW_LINE))

#define ONE_WIRE_READROM    0x33
#define ONE_WIRE_SKIPROM    0xcc
#define ONE_WIRE_SEARCHROM  0xf0
#define ONE_WIRE_MATCHROM   0x55

#ifndef ONEWIRE_H
#define	ONEWIRE_H

/**
 * 
 * @return 
 */
uint8_t OneWire_Presence(void);

/**
 * 
 * @param byte
 */
void OneWire_WriteByte(uint8_t byte);

/**
 * 
 * @return 
 */
uint8_t OneWire_ReadByte();

/**
 * 
 * @return 
 */
uint8_t OneWire_SkipROM();

/**
 * Читает ПЗУ подчиненного устройства. 
 * Использовать только если на шине одно подчиненной устройство!
 * @param buffer - куда складывать данные
 * @return "1" - если успешно прочиталось, "0" - если устройство не ответило
 */
uint8_t OneWire_ReadROM(uint8_t *buffer);

/**
 * 
 * @param buffer
 * @param len
 * @return 
 */
uint8_t OneWire_CRC8_Update(uint8_t *buffer, size_t len);

#endif	/* ONEWIRE_H */


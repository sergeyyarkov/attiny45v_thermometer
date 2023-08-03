#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "onewire.h"
#include "dstemperature.h"

#define DDR_TWI         DDRB
#define PORT_TWI        PORTB
#define PIN_TWI         PINB
#define PORT_TWI_DIO    PB0
#define PORT_TWI_CLK    PB2
#define PIN_TWI_DIO     PINB0
#define PIN_TWI_CLK     PINB2
#define TWI_DELAY       5           // uS

#define TM1637_DIGITS_COUNT 3

#define TM1637_DATA_CMD     0x40      // Data command setting
#define TM1637_DISP_CMD     0x80      // Display and control command setting
#define TM1637_ADDR_CMD     0xc0      // Address command setting

/**
 * Data write and read mode settings
 */
#define TM1637_WR_DATA      0x00      // Write data to display register
#define TM1637_RD_SCAN_DATA 0x02      // Read key scan data

/**
 * Address adding mode setting
 */
#define TM1637_ADDR_AUTO    0x00      // Automatic address adding
#define TM1637_ADDR_FIXED   0x04      // Fix address

/**
 * Test mode setting (for internal)
 */
#define TM1637_MODE_NORMAL  0x00      // Normal mode
#define TM1637_MODE_TEST    0x08      // Test mode

#define	TM1637_DISP_OFF     0x00      // Display off
#define	TM1637_DISP_ON      0x08      // Display on

#define dio_high()          (PORT_TWI |= (_BV(PORT_TWI_DIO)))
#define dio_low()           (PORT_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_input()         (DDR_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_output()        (DDR_TWI |= (_BV(PORT_TWI_DIO)))
#define clk_high()          (PORT_TWI |= (_BV(PORT_TWI_CLK)))
#define clk_low()           (PORT_TWI &= (~_BV(PORT_TWI_CLK)))

static const uint8_t display_symbols[] PROGMEM = 
{
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

void TWI_Start(void) {
  dio_high();
  clk_high();
  _delay_us(TWI_DELAY);
  dio_low();
  _delay_us(TWI_DELAY);
  clk_low();
}

void TWI_Stop(void) {
  clk_low();
  dio_low();
  _delay_us(TWI_DELAY);
  clk_high();
  _delay_us(TWI_DELAY);
  dio_high();
}

uint8_t TWI_WriteByte(uint8_t byte) {
  uint8_t i = 8;
  uint8_t ack = 0;
  
  _delay_us(TWI_DELAY);
  
  do {
    clk_low();
    _delay_us(TWI_DELAY);
    byte & 0x01 ? dio_high() : dio_low();
    byte >>= 1;
    _delay_us(TWI_DELAY);
    clk_high();
    _delay_us(TWI_DELAY);
  } while (--i);
  
  dio_input();
  clk_low();
  dio_high();
  
  _delay_us(TWI_DELAY);
  ack = bit_is_clear(PIN_TWI, PIN_TWI_DIO);
  
  clk_high();
  _delay_us(TWI_DELAY);
  clk_low();
  _delay_us(TWI_DELAY);
  dio_output();
  
  return ack;
}

void TM1637_WriteByte(uint8_t data) {
  TWI_Start();
  TWI_WriteByte(data);
  TWI_Stop();
} 

void TM1637_Init(uint8_t DIO_PIN, uint8_t CLK_PIN, uint8_t brightness, uint8_t enabled) {
  DDR_TWI |= _BV(DIO_PIN) | _BV(CLK_PIN);
  PORT_TWI &= ~(_BV(DIO_PIN) | _BV(CLK_PIN));
  TM1637_WriteByte(TM1637_DISP_CMD | (enabled | brightness));
}

void TM1637_DisplaySymbol(uint8_t symbol, uint8_t pos) {
  TM1637_WriteByte(TM1637_DATA_CMD);
  TWI_Start();
  TWI_WriteByte(TM1637_ADDR_CMD | pos);
  TWI_WriteByte(symbol);
  TWI_Stop();
}

void TM1637_DisplayUInt(uint16_t num) {
  uint16_t tmp = num > 999 ? 999 : num;
  uint8_t digits[TM1637_DIGITS_COUNT];
  uint8_t i = TM1637_DIGITS_COUNT;
  
  do {
    digits[i - 1] = tmp % 10;
    tmp /= 10;
  } while (--i);
  
  
  TM1637_DisplaySymbol(pgm_read_byte_near(&display_symbols[digits[0]]), 0);
  TM1637_DisplaySymbol(pgm_read_byte_near(&display_symbols[digits[1]]), 1);
  TM1637_DisplaySymbol(pgm_read_byte_near(&display_symbols[digits[2]]), 2);
}

void MCU_Init(void) {
  TM1637_Init(PORT_TWI_DIO, PORT_TWI_CLK, 1, TM1637_DISP_ON);
}

int main(void) {
  MCU_Init();
  
  DallasSensor Sensor_01;
  
  OneWire_ReadROM(Sensor_01.ROM);
    
  while (1) {
    DallasTemp_GetTemperature(&Sensor_01);
    TM1637_DisplayUInt(Sensor_01.TEMPERATURE);
  }
  return 0;
}
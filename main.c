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

#define TM1637_BRIGHTNESS_1 1
#define TM1637_BRIGHTNESS_2 2
#define TM1637_BRIGHTNESS_3 3
#define TM1637_BRIGHTNESS_4 4
#define TM1637_BRIGHTNESS_5 5
#define TM1637_BRIGHTNESS_6 6
#define TM1637_BRIGHTNESS_7 7

#define dio_high()          (PORT_TWI |= (_BV(PORT_TWI_DIO)))
#define dio_low()           (PORT_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_input()         (DDR_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_output()        (DDR_TWI |= (_BV(PORT_TWI_DIO)))
#define clk_high()          (PORT_TWI |= (_BV(PORT_TWI_CLK)))
#define clk_low()           (PORT_TWI &= (~_BV(PORT_TWI_CLK)))

#define get_symbol(index)   (pgm_read_byte_near(&display_symbols[index]))

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
	0x6F, // 9
};

void TWI_Start(void) {
  cli();
  dio_high();
  clk_high();
  _delay_us(TWI_DELAY);
  dio_low();
  _delay_us(TWI_DELAY);
  clk_low();
  sei();
}

void TWI_Stop(void) {
  cli();
  clk_low();
  dio_low();
  _delay_us(TWI_DELAY);
  clk_high();
  _delay_us(TWI_DELAY);
  dio_high();
  sei();
}

uint8_t TWI_WriteByte(uint8_t byte) {
  uint8_t i = 8;
  uint8_t ack = 0;
  
  cli();
  
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
  
  sei();
  
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

void TM1637_DisplayLine(void) {
  uint8_t i = TM1637_DIGITS_COUNT;
  do {
    TM1637_DisplaySymbol(0x40, i - 1);
  } while (--i);
}

void TM1637_DisplayInt(int16_t num) {
  uint8_t is_signed = num < 0;
  int16_t tmp = num > 999 ? 999 : num;
  uint8_t i = TM1637_DIGITS_COUNT;
  
  if (is_signed) {
    tmp = -tmp;
    TM1637_DisplaySymbol(0x40, 0); // sign symbol
  }
  
  do {
    if (is_signed && i == 1) break;
    TM1637_DisplaySymbol(pgm_read_byte_near(&display_symbols[tmp % 10]), i - 1);
    tmp /= 10;
  } while (--i);
}

uint8_t get_int_length(uint16_t num) {
  uint8_t l = 1;
  while (num > 9) {
    num /= 10;
    l++;
  }
  return l;
}


// TODO сделать отображение минусовой температуры для этой функции
void TM1637_DisplayFixedNum(int16_t num, uint8_t frac, uint8_t presicion) {
  uint8_t is_signed = (num < 0) | (num == 0 && frac > 0);
  num = num > 999 ? 999 : num;
  
  if (is_signed) {
    num = -num;
  }
  
  uint8_t length = get_int_length(num);
  uint8_t i = TM1637_DIGITS_COUNT, j = 0;
  uint8_t buffer[TM1637_DIGITS_COUNT];
  
  do {
    buffer[i - 1] = num % 10;
    num /= 10;
  } while (--i);

  if (length != 1) {
    i = TM1637_DIGITS_COUNT - length;
  } else {
    i = 1;
  }  
  
  while (i < TM1637_DIGITS_COUNT) {
//    if (j == 0) {
////      if (is_signed) {
////        TM1637_DisplaySymbol(0x40, 0);
////      }
//      i++;
//      j++;
//      continue;
//    }
    TM1637_DisplaySymbol(
            (j == TM1637_DIGITS_COUNT - 1 - presicion && TM1637_DIGITS_COUNT != length) 
            ? get_symbol(buffer[i]) | 0x80 // точка
            : get_symbol(buffer[i]),
            j);
    i++;
    j++;
  }
  
  TM1637_DisplaySymbol(get_symbol(frac), j);
}

int main(void) {
  DallasSensor Sensor_01;
  
  DallasTemp_SetResolution(&Sensor_01, 11);
  
  TM1637_Init(PORT_TWI_DIO, PORT_TWI_CLK, TM1637_BRIGHTNESS_2, TM1637_DISP_ON);
  TM1637_DisplayLine();
       
  while (1) {
    /**
     * Проверка датчика
     */
    if (DallasTemp_CheckError(&Sensor_01)) {
      TM1637_DisplayLine();
      continue;
    }
    
    /**
     * Получение температуры и вывод на индикатор
     */
    DallasTemp_GetTemperature(&Sensor_01);
    TM1637_DisplayFixedNum(Sensor_01.TEMPERATURE, Sensor_01.TEMPERATURE_FRACTION / 100, 1);
  }
  return 0;
}
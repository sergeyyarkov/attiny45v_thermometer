#include "tm1637.h"

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

uint8_t get_int_length(int16_t num) {
  uint8_t l = 1;
  if (num < 0) num = -num;
  while (num > 9) {
    num /= 10;
    l++;
  }
  return l;
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
    TM1637_DisplaySymbol(0x40, 0);
  }
  
  do {
    if (is_signed && i == 1) break;
    TM1637_DisplaySymbol(pgm_read_byte_near(&display_symbols[tmp % 10]), i - 1);
    tmp /= 10;
  } while (--i);
}

void TM1637_DisplayFixedNum(int16_t num, uint8_t frac, uint8_t presicion, uint8_t sign) {
  uint8_t is_signed = (num < 0) || (sign);
  num = num > 999 ? 999 : num;
  
  if (is_signed) {
    num = -num;
  }
  
  uint8_t length = get_int_length(num);
  uint8_t is_overflow = length + 1 == TM1637_DIGITS_COUNT;
  uint8_t i = TM1637_DIGITS_COUNT, j = is_overflow && is_signed ? 1 : 0;
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
    if (is_signed && j == 0) {
      TM1637_DisplaySymbol(0x40, 0);
      i++;
      j++;
      continue;
    }
    TM1637_DisplaySymbol(
            (j == TM1637_DIGITS_COUNT - 1 - presicion && TM1637_DIGITS_COUNT != length) 
            ? get_symbol(buffer[i]) | (is_overflow && is_signed ? 0 : 0x80) // точка
            : (!is_signed &&
                ((buffer[0] == 0 && buffer[i] == 0 && buffer[i + 1] != 0) || (length == 1 && i != TM1637_DIGITS_COUNT - 1)) // убираем вывод нулей
                ? 0x00 
                : get_symbol(buffer[i])
              ),
            j);
    i++;
    j++;
  }
  
  TM1637_DisplaySymbol(get_symbol(frac), j);
}

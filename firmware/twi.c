#include "twi.h"

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
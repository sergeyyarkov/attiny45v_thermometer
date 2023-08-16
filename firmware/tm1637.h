#include <avr/pgmspace.h>
#include "twi.h"

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

#ifndef TM1637_H
#define	TM1637_H


typedef struct TM1637Display {
  uint8_t DIO_PIN;
  uint8_t CLK_PIN;
  uint8_t BRIGHTNESS;
} TM1637Display;

void TM1637_WriteByte(uint8_t data);
void TM1637_Init(uint8_t DIO_PIN, uint8_t CLK_PIN, uint8_t brightness, uint8_t enabled);
void TM1637_DisplaySymbol(uint8_t symbol, uint8_t pos);
void TM1637_DisplayLine(void);
void TM1637_DisplayInt(int16_t num);
void TM1637_DisplayFixedNum(int16_t num, uint8_t frac, uint8_t presicion, uint8_t sign);

#endif	/* TM1637_H */


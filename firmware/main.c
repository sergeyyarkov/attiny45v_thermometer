#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "onewire.h"
#include "twi.h"
#include "tm1637.h"
#include "dstemperature.h"

#define ENABLE_ERROR_HANDLER 1

#define PIN_LED_ERR     PB1

/**
 * Обработка ошибки одного датчика
 * @param Sensor - датчик
 * @return "1" - есть ошибка, "0" - нет ошибки
 */
uint8_t SensorErrorHandler(DallasSensor *Sensor) {
  DallasSensorError error = DallasTemp_CheckError(Sensor);
  if (error) {
    switch (error) {
      case ERR_NO_PRESENCE:
        PORTB |= _BV(PIN_LED_ERR);
        TM1637_DisplayInt(error);
        break;
      case ERR_F_CODE_INVALID:
        break;
      case ERR_CRC8_RAM:
        break;
      default:
        break;
    }
    return 1;
  }
  
  PORTB &= ~_BV(PIN_LED_ERR);
  return 0;
}

int main(void) {
  DDRB |= _BV(PIN_LED_ERR);
  PORTB &= ~_BV(PIN_LED_ERR);
  
  wdt_reset();
  wdt_enable(WDTO_8S);
  
  DallasSensor Sensor_01;
  DallasTemp_SetResolution(&Sensor_01, DS_TEMP_ADC_RESOLUTION_12);
  
  TM1637_Init(PORT_TWI_DIO, PORT_TWI_CLK, TM1637_BRIGHTNESS_2, TM1637_DISP_ON);
  TM1637_DisplayLine();
  
  _delay_ms(100);
  
  sei();
  
  while (1) {
    #if ENABLE_ERROR_HANDLER 
      if (SensorErrorHandler(&Sensor_01)) {
        _delay_ms(50);
        wdt_reset();
        continue;
      } else {
        _delay_ms(10);
      }
    #endif
    
    /**
     * Получение температуры и вывод на индикатор
     */
    DallasTemp_GetTemperature(&Sensor_01);
    TM1637_DisplayFixedNum(Sensor_01.TEMPERATURE, Sensor_01.TEMPERATURE_FRACTION / 100, 1, Sensor_01.T_NEGATIVE);
    
    wdt_reset();
  }
  return 0;
}
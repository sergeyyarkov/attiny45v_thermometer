#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "onewire.h"
#include "dstemperature.h"

#define DDR_USI         DDRB
#define PORT_USI        PORTB
#define PIN_USI         PINB
#define PORT_USI_SDA    PB0
#define PORT_USI_SCL    PB2
#define PIN_USI_SDA     PINB0
#define PIN_USI_SCL     PINB2

void MCU_Init(void) {
  DDRB = _BV(PB1) | _BV(PB2);
  PORTB = 0x00;
}

int main(void) {
  MCU_Init();
  
  DallasSensor Sensor_01;
  
  while (1) {
    OneWire_ReadROM(Sensor_01.ROM);
    DallasTemp_GetTemperature(&Sensor_01);
    asm("nop");
  }
  return 0;
}
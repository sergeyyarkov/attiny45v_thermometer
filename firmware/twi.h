#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DDR_TWI         DDRB
#define PORT_TWI        PORTB
#define PIN_TWI         PINB
#define PORT_TWI_DIO    PB0
#define PORT_TWI_CLK    PB2
#define PIN_TWI_DIO     PINB0
#define PIN_TWI_CLK     PINB2
#define TWI_DELAY       5           // uS

#define dio_high()          (PORT_TWI |= (_BV(PORT_TWI_DIO)))
#define dio_low()           (PORT_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_input()         (DDR_TWI &= (~_BV(PORT_TWI_DIO)))
#define dio_output()        (DDR_TWI |= (_BV(PORT_TWI_DIO)))
#define clk_high()          (PORT_TWI |= (_BV(PORT_TWI_CLK)))
#define clk_low()           (PORT_TWI &= (~_BV(PORT_TWI_CLK)))

#ifndef TWI_H
#define	TWI_H

void TWI_Start(void);
void TWI_Stop(void);
uint8_t TWI_WriteByte(uint8_t byte);

#endif	/* TWI_H */


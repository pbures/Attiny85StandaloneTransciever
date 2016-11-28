#ifndef PINDEFS_H_
#define PINDEFS_H_

#define SET_INPUT_MODE(ddr,bit) ddr &= ~(1<<bit)
#define SET_OUTPUT_MODE(ddr,bit) ddr |= (1<<bit)
#define SET_HIGH(port,bit) port |= (1<<bit)
#define SET_LOW(port,bit) port &= ~(1<<bit)

/* Pin controlling the servo */
#define TRC_DDR 	DDRB
#define TRC_PORT 	PORTB
#define TRC_PIN 	PINB
#define TRC_BIT 	PB4

#define SIG_DDR 	DDRB
#define SIG_PORT 	PORTB
#define SIG_PIN 	PINB
#define SIG_BIT 	PB3

#endif /* PINDEFS_H_ */

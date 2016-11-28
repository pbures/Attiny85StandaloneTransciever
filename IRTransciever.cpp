/*
 * IRTransciever.cpp
 *
 *  Created on: 21. 11. 2016
 *      Author: pbures
 */

#include "IRTransciever.h"

IRTransciever::IRTransciever() {
	// TODO Auto-generated constructor stub
}

void IRTransciever::init() {

	/* Output mode on pin */
	SET_OUTPUT_MODE(TRC_DDR, TRC_BIT);
	SET_OUTPUT_MODE(SIG_DDR, SIG_BIT);

	IROff();

	/* CTC, Prescaler = 1 */
	TCCR1 |= ( _BV(CTC1) | _BV(CS10));

	/* Toggle OC1B pin on compare match, prescaler reset */
	GTCCR |= (_BV(COM1B0) | _BV(PSR1));

	/* Set to 38KhZ */
	OCR1B = 105; /* This makes it toggle the BP4 pin value */
	OCR1C = 105; /* This makes it reset to zero on value 105*/
}

void IRTransciever::send(uint8_t addr, uint8_t byte) {
	initialBurst();

	sendByte(addr);
	sendByte(byte);

	/* Finish the last bit */
	IROn();
	delay560us();
	IROff();
}

void IRTransciever::IROn() {
	//OCR0A = 105; // 8Mhz / 38 Khz. Blink every 210th tick, it is 105th up, 210th down. The time of one blink is 26us.
	TRC_DDR |= (1 << TRC_BIT);
	SET_HIGH(SIG_PORT, SIG_BIT);
}

void IRTransciever::IROff() {
	TRC_DDR &= ~(1 << TRC_BIT);
	SET_LOW(SIG_PORT, SIG_BIT);
}

void IRTransciever::initialBurst() {
	IROn();
	_delay_ms(9);
	IROff();
	_delay_ms(4);

	/* Can not call directly _delay_us(500) as max allowed value is 768/ F_CPU (in Mhz). */
	for (uint8_t i = 0; i < 6; i++) {
		_delay_us(500 / 6);
	}
}
void inline IRTransciever::delay560us() {
	for (uint8_t i = 0; i < 6; i++)
		_delay_us(560 / 6);
}

void inline IRTransciever::delay1200us() {
	for (uint8_t i = 0; i < 13; i++)
		_delay_us(1200 / 13);
}

void IRTransciever::sendByte(uint8_t byte) {

	/* Send the byte */
	for (int8_t b = 7; b >= 0; b--) {
		IROn();
		delay560us();
		IROff();
		if ((1 << b) & byte)
			delay1200us();
		else
			delay560us();
	}

	/* Send the inverted signal */
	for (int8_t b = 7; b >= 0; b--) {
		IROn();
		delay560us();
		IROff();
		if ((1 << b) & byte)
			delay560us();
		else
			delay1200us();
	}
}

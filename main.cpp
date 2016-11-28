#include <avr/io.h>
#include <util/delay.h>
#include "pindefs.h"

#include "IRTransciever.h"

void initSignal() {

	SET_OUTPUT_MODE(TRC_DDR, TRC_BIT);
	/* CTC, Prescaler = 1 */
	TCCR1 |= ( _BV(CTC1) | _BV(CS10));

	/* Toggle OC1B pin on compare match, prescaler reset */
	GTCCR |= (_BV(COM1B0) | _BV(PSR1));

	OCR1B = 105;
	OCR1C = 105;
}


int main() {


	IRTransciever::init();

	while(1) {
		IRTransciever::send(0, 'a');
		_delay_ms(50);

	}
}

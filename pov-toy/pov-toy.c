// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>

// ------ Functions ------//
void POVDisplay(uint8_t oneByte) {
	PORTB = oneByte;
	_delay_ms(5);
}

int main(void) {
	// ------ Inits ------ //
	DDRB = 0xFF;
	// ------ Event loop ------ //
	while (1) {
		// Space invader
		POVDisplay(0b00001110);
		POVDisplay(0b00011000);
		POVDisplay(0b10111110);
		POVDisplay(0b01101101);
		POVDisplay(0b00111101);
		POVDisplay(0b00111100);
		POVDisplay(0b00111101);
		POVDisplay(0b01101101);
		POVDisplay(0b10111110);
		POVDisplay(0b00011000);
		POVDisplay(0b00001110);
		
		
		/* Heart
		POVDisplay(0b01110000);
		POVDisplay(0b11111000);
		POVDisplay(0b11111100);
		POVDisplay(0b01111110);
		POVDisplay(0b00111111);
		POVDisplay(0b01111110);
		POVDisplay(0b11111100);
		POVDisplay(0b11111000);
		POVDisplay(0b01110000);
		*/
		
		PORTB = 0;
		_delay_ms(10);
	}
	return (0);
}
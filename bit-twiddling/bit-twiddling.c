// Practice with bitwise operation on PORTB

// ------ Preamble ------ //
#include <avr/io.h>                       // pins, ports, etc.
#include <util/delay.h>                   // delay functions
#include <avr/power.h>                    // clock speed

#define DELAYTIME 85                      // milliseconds
#define LED_PORT  PORTB
#define LED_DDR   DDRB

// ------ Main ------ //
int main(void) {
	clock_prescale_set(clock_div_8);
	
	uint8_t i;
	uint8_t repetitions;
	uint8_t whichLED;
	uint16_t randomNumber = 0x1234;
	
	// ------ Inits ------ //
	LED_DDR = 0xFF;                       // DDRB configured for output
	// ------ Event loop ------ //
	while (1){
		                                  // go left, turn on LEDs, turn off LEDs
		for (i = 0; i < 8; i++){
			LED_PORT |= (1 << i);         // turn on the i'th pin
			_delay_ms(DELAYTIME);         // wait
		}
		for (i = 0; i < 8; i++){
			LED_PORT &= ~(1 << i);        // turn off the i'th pin
			_delay_ms(DELAYTIME);         // wait
		}
		_delay_ms(5 * DELAYTIME);         // pause
		                                  
										  // go right, turn on LEDs, turn off LEDs
		for (i = 7; i < 255; i--){
			LED_PORT |= (1 << i);         // turn on the i'th pin
			_delay_ms(DELAYTIME);         // wait
		}
		for (i = 7; i < 255; i--){
			LED_PORT &= ~(1 << i);        // turn off the i'th pin
			_delay_ms(DELAYTIME);         // wait
		}
		_delay_ms(DELAYTIME);             // pause
		
		                                  // toggle "random" bits for a while
		for (repetitions = 0; repetitions < 75; repetitions++){
			                              // "random" number generator
			randomNumber = 2053 * randomNumber + 13849; 
			                              // low three bits from high byte
			whichLED = (randomNumber >> 8) & 0b00000111;
			LED_PORT ^= (1 << whichLED);  // toggle LEDs
			_delay_ms(DELAYTIME);
		}
		LED_PORT = 0;                     // all LEDs off
		_delay_ms(5 * DELAYTIME);         // pause
		
	}                                     // end event loop
	return(0);
}
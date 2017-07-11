/* A simple test of serial-port functionality.
   Takes in a character at a time and sends it back out,
   displaying the ASCII value on LEDs. */
// Uses an external 8MHz crystal oscillator

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "pinDefines.h"
#include "USART.h"

FUSES = 
{
  .low = (FUSE_SUT1 & FUSE_SUT0 & FUSE_CKSEL2 & FUSE_CKSEL1 & FUSE_CKSEL0),
  .high = HFUSE_DEFAULT,
  .extended = EFUSE_DEFAULT,
};

// ------ Main ------ //
int main(void) {

  clock_prescale_set(clock_div_4);
	char serialCharacter;
	
	// ------ Inits ------ // 
//  LED_DDR = 0xFF;                            // LEDs set up for output
	initUSART();
	printString("Hello World!\r\n");          // To test
	
	// ------ Event loop ------ //
	while(1) {
		
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
//		LED_PORT = serialCharacter;             // display ASCII value of character
		
	}                                         // End event loop
	return(0);
}
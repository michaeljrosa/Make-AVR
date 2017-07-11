// Simple on/off button code, no debouncing

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>

FUSES = {

  .low = LFUSE_DEFAULT,
  .high = HFUSE_DEFAULT,
  .extended = EFUSE_DEFAULT,

};

int main(void) {
  // ------ Inits ------ //
  DDRD &= ~(1 << PD2);              // button input
  PORTD |= (1 << PD2);              // button pull-up resistor
  DDRB = 0xFF;                      // LED output
  
  // ------ Main loop ------ // 
  while(1) {
    if(bit_is_clear(PIND, PD2)) {   // look for button press
                                    // equiv. to if((PIND & (1 << PD2)) == 0)
      PORTB = 0b00111100;           // pressed
    }
    else {                          // not pressed
      PORTB = 0b11000011;
    }
  }                                 // end event loop
  return(0);
}
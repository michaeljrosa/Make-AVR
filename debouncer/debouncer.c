// toggle_button.c with debounce code

// ------ Preamble ------ // 
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

#define  DELAY_TIME  10000                   // microseconds

uint8_t debounce(void) {
  if(bit_is_clear(BUTTON_PIN, BUTTON)) {     // button is pressed
    _delay_us(DELAY_TIME);
    if(bit_is_clear(BUTTON_PIN, BUTTON)) {
      return(1);
    }
  }
  return(0);
} 

// ------ Main ------ //
int main(void) {
  // ------ Inits ------ //
  uint8_t buttonWasPressed;                  // state
  DDRD &= ~(1 << BUTTON);                    // set button for input
  BUTTON_PORT |= (1 << BUTTON);              // enable pull-up on button
  LED_DDR = (1 << LED0);                     // set LED for output
  
  // ------ Event loop ------ //
  while(1) {
    if(debounce()) {                         // debounced button press
      if(buttonWasPressed == 0) {            // but wasn't last time through
        LED_PORT ^= (1 << LED0);             // do whatever
        buttonWasPressed = 1;                // update the state
      }
    }
    else {                                   // button is not pressed now
      buttonWasPressed = 0;                  // update the state
    }
  }                                          // end event loop
  return(0);
}
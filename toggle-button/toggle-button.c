// Demonstrates using state to detect button presses

// ------ Preamble ------ // 
#include <avr/io.h>
#include "pinDefines.h"

// ------ Main ------ //
int main(void) {
  // ------ Inits ------ //
  uint8_t buttonWasPressed;                  // state
  DDRD &= ~(1 << BUTTON);                    // set button for input
  BUTTON_PORT |= (1 << BUTTON);              // enable pull-up on button
  LED_DDR = (1 << LED0);                     // set LED for output
  
  // ------ Event loop ------ //
  while(1) {
    if(bit_is_clear(BUTTON_PIN, BUTTON)) {   // button is pressed now
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
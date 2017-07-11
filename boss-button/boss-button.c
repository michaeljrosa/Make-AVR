// Signals a desktop script to launch a web-page

// ------ Preamble ------ //
#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.H"

FUSES = {
  .low = (FUSE_CKSEL2 & FUSE_CKSEL1 & FUSE_CKSEL0 & FUSE_SUT1 & FUSE_SUT0), 
  .high = HFUSE_DEFAULT,  
  .extended = EFUSE_DEFAULT, 
};

// ------ Functins ------ //
static inline void blinkLED(void) {
  LED_PORT |= (1 << LED0);
  _delay_ms(1000);
  LED_PORT &= ~(1 << LED0);
}

// ------ Main ------ //
int main(void) {
  
  // ------ Inits ------ //
  clock_prescale_set(clock_div_4);
  
  BUTTON_DDR &= ~(1 << BUTTON);
  BUTTON_PORT |= (1 << BUTTON);
  
  LED_DDR |= (1 << LED0);
  blinkLED();
  
  initUSART();
  transmitByte('0');
  
  // ------ Event loop ------ //
  while(1) {
    if(bit_is_clear(BUTTON_PIN, BUTTON)) {
      transmitByte('X');
      blinkLED();
    }
  }
  
  return(0);
}
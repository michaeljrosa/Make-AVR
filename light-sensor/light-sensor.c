// quick demo of light sensor 

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

FUSES = {
  .low = LFUSE_DEFAULT, 
  .high = HFUSE_DEFAULT, 
  .extended = EFUSE_DEFAULT, 
};

// ------ Functions ------ //
static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);                           // reference voltage on AVCC
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);           // ADC clock prescaler /8
  ADCSRA |= (1 << ADEN);                           // enable ADC
}

// ------ Main ------ //
int main(void) {
  
  // ------ Inits ------ //
  uint8_t ledValue;
  uint16_t adcValue;
  uint8_t i;
  initADC0();
  LED_DDR = 0xFF;
  
  // ------ Event loop ------ //
  while(1) {
    
    ADCSRA |= (1 << ADSC);                         // start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);         // wait until done
    adcValue = ADC;                                // read ADC in
    ledValue = (adcValue >> 7);                    // have 10 bits, want 3 (for 8 LEDS)
                                                   // light up LED up to ledValue
    LED_PORT = 0;
    for (i = 0; i <= ledValue; i++) {
      LED_PORT |= (1 << i);
    }
    _delay_ms(50);
  }                                                // end event loop
  return(0);
}
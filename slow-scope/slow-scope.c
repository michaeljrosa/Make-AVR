// Slow-scope. A free running AVR / ADC "oscilloscope"

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

#define SAMPLE_DELAY 20       // ms, controls the scroll-speed of the scope

// ------ Functions ------ //
static inline void initFreerunningADC(void)
{
  ADMUX |= 1 << REFS0;         // v-ref on AVCC
  ADMUX |= 1 << ADLAR;         // left-adjust result
  
  ADCSRA |= 1 << ADPS1 | 1 << ADPS0;     // prescaler 8
  ADCSRA |= 1 << ADEN;         // ADC enable
  ADCSRA |= 1 << ADATE;        // auto-trigger enable
  ADCSRA |= 1 << ADSC;         // start the first conversion
}

int main(void)
{
  // ------ Inits ------ //
  initUSART();
  initFreerunningADC();
  
  // ------ Event loop ------ //
  while(1)
  {
    transmitByte(ADCH);         // transmit the high byte, left-adjusted
    _delay_ms(SAMPLE_DELAY);
  }
  
  return 0;
}
// Music box input demo

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"

#define  SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))

// ------ Main ------ //
int main(void) {
  const uint16_t song[] = {
    E6, E6, E6, C6, E6, G6, G5,
    C6, G5, E5, A5, B5, Ax5, A5,
    G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
    C6, G5, E5, A5, B5, Ax5, A5,
    G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
  };                                                          // etc
  // starting at end b/c routine starts by incrementing and then playing
  // this makes the song start at the beginning after reboot
  uint8_t whichNote = SONG_LENGTH - 1;
  uint8_t wasButtonPressed = 0;
  
  // ------ Inits ------ //
  SPEAKER_DDR |= (1 << SPEAKER);                              // speaker for output
  BUTTON_DDR &= ~(1 << BUTTON);                               // button for input
  BUTTON_PORT |= (1 << BUTTON);                               // button pull-up
  LED_DDR |= (1 << LED0);                                     // LED for output
  
  // ------ Event loop ------ //
  while(1) {
    if(bit_is_clear(BUTTON_PIN, BUTTON)) {
      LED_PORT = (1 << LED0);
      if(!wasButtonPressed) {                                 // if it's a new press
        whichNote++;                                          // advance to next note
                                                              // but don't run over the end
        if(whichNote == SONG_LENGTH) {
          whichNote = 0;
        }
        wasButtonPressed = 1;
      }
      playNote(song[whichNote], 1600);
    }
    else {
      wasButtonPressed = 0;
      LED_PORT = (0 << LED0);
    }
  }
  return(0);
}
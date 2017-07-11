// Reads a character in serial from the keyboard, plays a note.

// ------ Preamble ------ //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"
#include "USART.h"

#define  NOTE_DURATION    0xF000             // determines long note length

FUSES = {
  .low = (FUSE_SUT1 & FUSE_SUT0 & FUSE_CKSEL2 & FUSE_CKSEL1 & FUSE_CKSEL0),
  .high = HFUSE_DEFAULT,
  .extended = EFUSE_DEFAULT,
};

int main(void) {
  
  
  // ------ Inits ------ //
  clock_prescale_set(clock_div_4);
  SPEAKER_DDR |= (1 << SPEAKER);             // speaker for output
  initUSART();
  printString("------ Seial Organ -------\r\n");
  
  char fromCompy;                            // used to store serial input
  uint16_t currentNoteLength = NOTE_DURATION / 2;
  const uint8_t keys[] = {
    'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y',
    'h', 'j', 'i', 'k', 'o', 'l', 'p', ';', '\''
  };
  const uint16_t notes[] = {
    G4, Gx4, A4, Ax4, B4, C5, Cx5, D5, Dx5, 
    E5, F5, Fx5, G5, Gx5, A5, Ax5, B5, C6
  };
  uint8_t isNote;
  uint8_t i;
  
  
  // ------ Event loop ------ //
  while(1) {
                                             // get key
    fromCompy = receiveByte();               // waits here until input
    transmitByte('N');                       // alert computer we're ready for next note
    
                                             // play note
    isNote = 0;
    for(i = 0; i < sizeof(keys); i++) {
      if(fromCompy == keys[i]) {             // fount match in lookup table
        playNote(notes[i], currentNoteLength);
        isNote = 1;                          // record that note is found
        break;                               // drop out of for() loop
      }
    }
    
                                             // non-note keyas: temp change, rests
    if(!isNote) {
      if(fromCompy == '[') {                 // code for short note
        currentNoteLength = NOTE_DURATION / 2;
      }
      else if(fromCompy == ']') {            // code for long note
        currentNoteLength = NOTE_DURATION;
      }
      else {                                 // unrecognized, just rest
        rest(currentNoteLength);
      }
    }
    
  }                                          // end event loop
  return(0);
}
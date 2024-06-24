#include "pitches.h"
#include "constants.h"

int indiana_jones[][2] = {
  {NOTE_FS4, 300}, {NOTE_G4, 200}, {NOTE_A4, 250}, {NOTE_D5, 700}, 
  {NOTE_F4, 300}, {NOTE_FS4, 250}, {NOTE_G4, 700},
  {NOTE_A4, 300}, {NOTE_B4, 300}, {NOTE_CS5, 300}, {NOTE_G5, 600},
  {NOTE_B4, 300}, {NOTE_CS5, 300}, {NOTE_D5, 500}, {NOTE_E5, 550}, {NOTE_FS5, 600},
  {NOTE_FS4, 300}, {NOTE_G4, 300}, {NOTE_A4, 300}, {NOTE_D5, 600}, 
  {NOTE_E5, 300}, {NOTE_FS5, 300}, {NOTE_G5, 900},
  {NOTE_A4, 300}, {NOTE_A4, 300}, {NOTE_FS5, 500}, {NOTE_E5, 300}, {NOTE_A4, 300}, {NOTE_FS5, 500}, {NOTE_E5, 600},
  {NOTE_A4, 300}, {NOTE_FS5, 500}, {NOTE_E5, 600},
  {NOTE_A4, 300}, {NOTE_G5, 300}, {NOTE_FS5, 300}, {NOTE_E5, 600}, {NOTE_D5, 1200},
};

int melody[][2] = {
  {NOTE_G4, 200}, {NOTE_C5, 200}, {NOTE_E5, 200},
  {0, 200},
  {NOTE_E5, 200}, {NOTE_C5, 200}, {NOTE_G4, 200},
  {0, 200},
  {NOTE_G4, 200}, {NOTE_C5, 200}, {NOTE_E5, 200}, {NOTE_F5, 200},
  {NOTE_E5, 200}, {NOTE_C5, 200}, {NOTE_G4, 200},
};

int melody_short[][2] = {
  {NOTE_G4, 200}, {NOTE_C5, 200}, {NOTE_E5, 200},
  {0, 200},
  {NOTE_E5, 200}, {NOTE_C5, 200}, {NOTE_G4, 200},
};

int mario[][2] = {
  
  {NOTE_C7, 500}, {NOTE_G6, 400}, {NOTE_E6, 500}, 
  {NOTE_A6, 200}, {0, 200}, {NOTE_B6, 200}, {0, 200}, {NOTE_AS6, 200}, {NOTE_A6, 200}, {0, 200},
  
  {NOTE_G6, 200}, {NOTE_E7, 200}, {NOTE_G7, 200},
  {NOTE_A7, 200}, {0, 200}, {NOTE_F7, 200}, {NOTE_G7, 200}, {0, 200},
  {NOTE_E7, 200}, {0, 200}, {NOTE_C7, 200}, {NOTE_D7, 200}, {NOTE_B6, 200}, {0, 200}, {0, 200},
};

void sound() {
  bool wasShown = false;

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    if (!wasShown) {
      printAllSegments(17, 255);
      wasShown = true;
    } else {
      turnOffAllSegments();
      wasShown = false;
    }

    tone(5, melody[i][0], melody[i][1]);
    delay(melody[i][1] * 1.30);
    noTone(5);
  }
}
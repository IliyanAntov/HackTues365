#include "MorseCodeGame.h"
#include "ButtonGame.h"
#include "Timer.h"
#include "ArduinoRead.h"

void setup() {
   setupTimer();
   while (!loadInputs()) {}

   setupButtonGame(RGBColor, wantedDigit);
   setupMorseCode(wordIndex, morseCodeWord);
   setupSimonSaysGame(buttonOrder, sequence);
}

void loop() {
    if (tickTimer()) {
        if (tickMorseCode() < 0) {
            //wrong
        }
        if (tickButtonGame() < 0) {

        }
        if (tickSimonSaysGame() < 0) {
            //wrong
        }
    } else {
        
    }
}

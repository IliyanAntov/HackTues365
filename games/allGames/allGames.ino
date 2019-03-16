#include "MorseCodeGame.h"
#include "ButtonGame.h"
#include "Timer.h"
#include "ArduinoRead.h"

void setup() {
   setupTimer();
   while (!loadInputs()) {}


   setupMorseCode();
   setupButtonGame('R', 5, 5);
}

void loop() {
    if (tickTimer()) {
        tickMorseCode();
        tickButtonGame();
    } else {
        Serial.println("nz i az");
    }
}

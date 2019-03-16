#include "MorseCodeGame.h"
#include "ButtonGame.h"
#include "timer.h"

void setup() {
   setupMorseCode();
   setupButtonGame();
   setupTimer();

   Serial.begin(9600);
}

void loop() {
   if(!tickTimer()){
        tickMorseCode();
        tickButtonGame();
   }else{
       Serial.println("nz i az");
   }
}

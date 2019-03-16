#include "MorseCodeGame.h"
#include "ButtonGame.h"
#include "timer.h"

void setup() {
   setupMorseCode();
   setupButtonGame('R',5,5); //just for now
   setupTimer();

   Serial.begin(9600);
}

void loop() {
    Serial.println(getTime()[0]);
    Serial.println(getTime()[1]);
    if(tickTimer()){
        tickMorseCode();
        tickButtonGame();
    }else{
        Serial.println("nz i az");
    }
}

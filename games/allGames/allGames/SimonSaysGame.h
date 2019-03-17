#include "Button.h"

int lights[4] = {28, 29, 30, 31};
int buttonPins[4] = {32, 33, 34, 35};
//int *seed;
int seed[] = {0, 1, 2, 3, 0, 1};
int index = 0;

Button buttons[4];
Delay lightDelay;
bool doLight;
bool flashed = false;
int currentLED = 0;
int lightPattern() {
    if (!doLight) {
        return 0;
    }
    
    if (lightDelay.started() && !lightDelay.elapsed()) {   
        return 0;
    }
    
    if (currentLED < index+1) {
        if (!flashed) {
            digitalWrite(lights[seed[currentLED]], HIGH);
            lightDelay.restart();
            lightDelay.start();
            flashed = true;
            return 0;
        }
        digitalWrite(lights[seed[currentLED]], LOW);
            
        lightDelay.restart();
        lightDelay.start();
        flashed = false;
        currentLED++;
    } else {
        currentLED = 0;
        doLight = false;
    }
}

void setupSimonSaysGame(int *btns, int* lts) {
    for (int i = 0; i < 4; i++) {
        pinMode(lights[i], OUTPUT);
        digitalWrite(lights[i], LOW);
        pinMode(buttonPins[i], INPUT_PULLUP);
        
        buttons[i].setPin(buttonPins[btns[i]]);
    }
    for (int i = 0; i < 6; i++) {
        seed[i]= lts[i]; 
    }
    doLight = true;
    lightDelay.set_milliseconds(300);
}

bool checkInput(int current) {
    return !(digitalRead(buttonPins[seed[current]]));
}

int currentButton = 0;
int tickSimonSaysGame() {
     //TODO: put less resistance
      if (currentButton == 0 && index == 0) {
          doLight = true;
      }
      
      for (int i = 0; i < 4; i++) {
          if (buttons[i].isClicked()) {
              if (checkInput(currentButton)) {
                  currentButton++;
              } else {
                  index = 0;
                  currentButton = 0;
                  return -1;
              }
  
              if (currentButton > index) {
                  if (++index == 6 ) {
                      pinMode(A0, OUTPUT);
                      digitalWrite(A0, HIGH);
                      return 1;
                  }
                  currentButton = 0;
                  doLight = true;
              }
          }
      }
      
      lightPattern();
      
      return 0;
}

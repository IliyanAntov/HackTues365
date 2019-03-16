#include "timer.h"
#include "Button.h"

int b_buttonPin = 22;
int b_common_cathode = 23;
int b_red_anode = 24;
int b_green_anode = 25;
int b_blue_anode = 26;

int b_buttonState = 1;

char b_rgbColor;
int b_wantedDigitStart;
int b_wantedDigitEnd;

void turnOnRGB(int R, int G, int B){
  digitalWrite(b_red_anode, R);
  digitalWrite(b_green_anode, G);
  digitalWrite(b_blue_anode, B);
  digitalWrite(b_common_cathode, LOW);
}

void turnOffRGB(){
  digitalWrite(b_red_anode,LOW);
  digitalWrite(b_green_anode,LOW);
  digitalWrite(b_blue_anode,LOW);
  digitalWrite(b_common_cathode,HIGH);
}

void lightRGB(char color) {
  switch(color){
    case 'R':
      turnOnRGB(1,0,0);
      break;
    case 'G':
      turnOnRGB(0,1,0);
      break;
    case 'B':
      turnOnRGB(0,0,1);
      break;
    case 'Y':
      turnOnRGB(1,1,0);
      break;
  }
}

int digitInTimer(int wantedDigit){
    return(getTimer()[1]%10 == wantedDigit || getTimer()[1]/10 == wantedDigit || getTimer()[0] == wantedDigit);
}

int tickButtonGame() {
    Serial.println()
    if (!digitalRead(b_buttonPin) && b_buttonState == 1) {
        b_buttonState = -1;
        if (digitInTimer(b_wantedDigitStart)) {
            //right moment
            lightRGB(b_rgbColor);
            if (digitalRead(b_buttonPin)) {
                b_buttonState = 1;
                turnOffRGB();
                if (digitInTimer(b_wantedDigitEnd)) {
                    return 1;
                } else {
                    return -1;
                }
            }
        } else {
            turnOffRGB();
            return -1;
        }
    }
    return 0;
}

void setupButtonGame(char color, char digitStart, char digitEnd){
    b_rgbColor = color;
    b_wantedDigitStart = digitStart;
    b_wantedDigitEnd = digitEnd;

    pinMode(b_buttonPin,INPUT);
    for (int i = 22; i < 27; i++) {
        pinMode(i, OUTPUT);
    }
    turnOffRGB();
}

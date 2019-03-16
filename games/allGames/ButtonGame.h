#include <Game.h>


int timeToPress = 3;
char colors[4] = {'R','G','B','Y'};
int buttonPin = 3;
int common_cathode = 10;
int red_anode = 11;
int green_anode = 12;
int blue_anode = 13;

int fakeTimer = 3;

int buttonState = 1;

int buttonGame() {
    if (!digitalRead(buttonPin) && buttonState == 1) {
        buttonState = -1;
        if (fakeTimer == timeToPress) {
            //right moment
            int index = random(4);
            char color = colors[index];
            while (buttonState == -1) {
                lightRGB(color);
                if (digitalRead(buttonPin)) {
                    buttonState = 1;
                    turnOffRGB();
                    if (fakeTimer == timeToPress) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            }
        } else {
            turnOffRGB();
            return -1
        }
    }
    return 0;
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

void turnOnRGB(int R, int G, int B){
  digitalWrite(red_anode,R);
  digitalWrite(green_anode,G);
  digitalWrite(blue_anode,B);
  digitalWrite(common_cathode,LOW);
}

void turnOffRGB(){
  digitalWrite(red_anode,LOW);
  digitalWrite(green_anode,LOW);
  digitalWrite(blue_anode,LOW);
  digitalWrite(common_cathode,HIGH);
}

class ButtonGame : public Game {
public:
    ButtonGame() {
        randomSeed(analogRead(0));
        pinMode(buttonPin,INPUT);
        for (int i = 10;i<14;i++) {
            pinMode(i,OUTPUT);
        }
        turnOffRGB();

    }

    int tick() {
        return buttonGame();
    }
}
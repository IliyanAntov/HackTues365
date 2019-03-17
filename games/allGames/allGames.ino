#include "MorseCodeGame.h"
#include "SimonSaysGame.h"
#include "ButtonGame.h"
#include "Timer.h"
#include "ArduinoRead.h"

int tries = 2;
int redLeds[tries] = {41, 42};
int greenLeds[3] = {38,39,40};
bool gameOver = false;

int tickMorseCodeReturn;
int tickButtonGameReturn;
int tickSimonSaysGameReturn;

bool completed[3] = {false, false, false};

void setup() {
    for (int i = 38; i < 43; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }

    setupTimer();
    setupReading();
    while (!loadInputs()) {Serial.print("loading");}

    setupButtonGame(RGBColor, wantedDigit);
//   setupMorseCode(wordIndex, morseCodeWord);
//   setupSimonSaysGame(buttonOrder, sequence);
}

void loop() {
    displayStrikes(tries);
    if (tickTimer() && !gameOver) { //wrong
        tickMorseCodeReturn = tickMorseCode();
        tickButtonGameReturn = tickButtonGame();
        tickSimonSaysGameReturn = tickSimonSaysGame();

        if (!completed[0]) {
            if (tickMorseCodeReturn < 0) {
                checkTries();
            } else if (tickMorseCodeReturn == 1) {  //Game completed
                completed[0] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
        if (!completed[1]) {
            if (tickButtonGameReturn < 0) {
                checkTries();
            } else if (tickButtonGameReturn == 1) {
                completed[1] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
        if (!completed[2]) {
            if (tickSimonSaysGameReturn < 0) {
                checkTries();
            } else if (tickSimonSaysGameReturn == 1) {
                completed[2] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
    } else {
        //GAME OVER
        Serial.println("Game over");
    }
}

void checkTries() {
    if (tries >= 1) {
        tries--;
    } else {
        gameOver = true;
    }
}

void displayStrikes(int strikes) {
    switch (strikes) {
        case 1:
            digitalWrite(redLeds[0], HIGH);
            digitalWrite(redLeds[1], LOW);
            break;
        case 2:
            digitalWrite(redLeds[0], HIGH);
            digitalWrite(redLeds[1], HIGH);
            break;
    }
}

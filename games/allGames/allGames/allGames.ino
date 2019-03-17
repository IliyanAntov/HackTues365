#include "MorseCodeGame.h"
#include "SimonSaysGame.h"
#include "ButtonGame.h"
#include "Timer.h"
#include "ArduinoRead.h"

int redLeds[] = {41, 42};
int greenLeds[] = {38, 39, 40};
int wrongAnswers = 0;
bool gameOver = false;

int tickMorseCodeReturn;
int tickButtonGameReturn;
int tickSimonSaysGameReturn;

bool completed[3] = {false, false, false};

int rgbString[] = {'R', 'G', 'B'};

void setup() {
    for (int i = 38; i < 43; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    Serial.begin(9600);
    setupTimer();
//    setupReading();
//    while (!loadInputs()) {}

    setupButtonGame('R', 5);
    int word[] = {'F', 'O', 'X'};
    setupMorseCodeGame(1, word);
    int arr[] = {1, 0, 2, 3};
    int seq[] = {0, 1, 2, 3, 0, 1};
    setupSimonSaysGame(arr, seq);
}

void loop() {
//    displayStrikes(tries);
    if (tickTimer() > 0) { //wrong
        tickMorseCodeReturn = tickMorseCodeGame();
        tickButtonGameReturn = tickButtonGame();
        //tickSimonSaysGameReturn = tickSimonSaysGame();

        if (!completed[0]) {
            if (tickMorseCodeReturn < 0) {
            } else if (tickMorseCodeReturn == 1) {  //Game completed
                completed[0] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
        if (!completed[1]) {
            if (tickButtonGameReturn < 0) {
            } else if (tickButtonGameReturn == 1) {
                completed[1] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
        if (!completed[2]) {
            if (tickSimonSaysGameReturn < 0) {
            } else if (tickSimonSaysGameReturn == 1) {
                completed[2] = true;
            }
        } else {
            digitalWrite(greenLeds[0], HIGH);
        }
    } else {
        //smyrt
    }
}

void displayStrikes(int strikes) {
    digitalWrite(redLeds[strikes], HIGH);
}

//dot - 0
//dash - 1

//hardcode incoming
// | | |
// v v v

#include "Delay.h"

char morse_code_mapping[][5] = {
  "01", //A -> .-
  "1000", //B -> -...
  "1010", //C -> -.-.
  "100", //D -> -..
  "0", //E -> .
  "0010", //F -> ..-.
  "110", //G -> --.
  "0000", //H -> ....
  "00", //I -> ..
  "0111", //J -> .---
  "101", //K -> -.-
  "0100", //L -> .-..
  "11", //M -> --
  "10", //N -> -.
  "111", //O -> ---
  "0110" //P -> .--.
  "1101", //Q -> --.-
  "010", //R -> .-.
  "000", //S -> ...
  "1", //T -> -
  "001", //U -> ..-
  "0001", //V -> ...-
  "011", //W -> .--
  "1001", //X -> -..-
  "1011", //Y -> -.--
  "1100" //Z -> --..
};

//WE HAVE TO CHANGE THE PIN NUMBERS TO BE MORE SEQUENCIAL ONCE WE PUT EVERYTHING ON ONE ARDUINO !!!

int input_word[3] = {4, 7, 8};
int num_to_display = 5;

int potentiometer = 14;
int led = 7;
int buttonPin = 15;

int dot_delay = 300;
int dash_delay = 700;
int pause_btw_letters = 1500;
int pause_btw_reset = 3000;

char Numbers[16][8] = {
              "abcdef",
              "bc",
              "abged",
              "abcgd",
              "bcgf",
              "afgcd",
              "afedcg",
              "abc",
              "abcdefg",
              "gfabcd",
              "abcefg",
              "fedcg",
              "afed",
              "bcdeg",
              "afged",
              "afge"
          };

int OA1 = 0;
int aPin = A2;
int bPin = 2;
int cPin = 4;
int dPin = 5;
int ePin = 6;
int fPin = 8;
int gPin = 9;


void setup() {
  pinMode(potentiometer, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);

  for (int i = 4; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(OA1, OUTPUT);
  digitalWrite(OA1, LOW);
  digitalWrite(led, LOW);

  Serial.begin(9600);
}

void loop() {
    show_morse();
    read_input();
}

int currentLetter = 0;
int currentChar = 0;
Delay lightOnDelay;
Delay lightOffDelay;

void show_morse() {
    if (lightOnDelay.started()) {
        if (!lightOnDelay.elapsed()) {
            return;
        }
        //has elapsed
        lightOnDelay.restart();
        digitalWrite(led, LOW);
        int pause_time = 200;
        if (currentChar == 0) {
            pause_time = pause_btw_letters;
        }
        if (currentLetter == 3) {
            pause_time = pause_btw_reset;
            currentLetter = 0;
        }
        lightOffDelay.set_milliseconds(pause_time);
        lightOffDelay.start();
    }

    if (lightOffDelay.started()) {
        if (!lightOffDelay.elapsed()) {
            return;
        }
        //has elapsed
        lightOffDelay.restart();
    }

    char* current = morse_code_mapping[input_word[currentLetter]];

    digitalWrite(led, HIGH);
    if (current[currentChar] == '0') {
        lightOnDelay.set_milliseconds(dot_delay);
    } else {
        lightOnDelay.set_milliseconds(dash_delay);
    }
    lightOnDelay.start();
    if (++currentChar == strlen(current)) {
        currentChar = 0;
        currentLetter++;
    }
}

void read_input(){
    int t = analogRead(potentiometer);
    t = map(t, 0, 1020, 0, 15);

    write_digit(Numbers[t]);
    light_digit();

    if (!digitalRead(buttonPin)) {
        if (t == num_to_display) {
            Serial.println("brao ludko");
        } else {
            Serial.println("failure");
        }
    }
}

void write_digit(char num[8]) {
    for(int j = 0; j < strlen(num); j++){
          char letter = num[j];
        switch(letter){
          case 'a':
              digitalWrite(aPin, LOW);
              break;
          case 'b':
              digitalWrite(bPin, LOW);
              break;
          case 'c':
              digitalWrite(cPin, LOW);
              break;
          case 'd':
              digitalWrite(dPin, LOW);
              break;
          case 'e':
              digitalWrite(ePin, LOW);
              break;
          case 'f':
              digitalWrite(fPin, LOW);
              break;
          case 'g':
              digitalWrite(gPin, LOW);
              break;
        }
    }
}

void light_digit(){
    digitalWrite(OA1, HIGH);
    delay(3);
    for(int i = 2; i < 10; i++){
      if(i!=3 && i!=7){
       digitalWrite(i, HIGH);
      }
   }
   digitalWrite(A2,HIGH);
}

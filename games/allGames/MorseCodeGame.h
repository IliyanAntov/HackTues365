#include "sevenSegment.h"
#include "Delay.h"

char m_mapping[26][5] = {
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

int m_random_words[3] = {4, 7, 8};
int m_num_to_display = 5;

int m_potentiometer = 12;
int m_led = 13;
int buttonPin = 14;

int m_OA1 = 15;
int m_indicator_pins[] = {16, 17, 18, 19, 20, 21, 22};



int m_dot_delay = 300;
int m_dash_delay = 700;
int m_pause_btw_letters = 1500;
int m_pause_btw_reset = 3000;


int m_currentLetter = 0;
int m_currentChar = 0;
Delay m_lightOnDelay;
Delay m_lightOffDelay;

void show_morse() {
    if (m_lightOnDelay.started()) {
        if (!m_lightOnDelay.elapsed()) {
            return;
        }
        //has elapsed
        m_lightOnDelay.restart();
        digitalWrite(m_led, LOW);
        int pause_time = 200;
        if (m_currentChar == 0) {
            pause_time = m_pause_btw_letters;
        }
        if (m_currentLetter == 3) {
            pause_time = m_pause_btw_reset;
            m_currentLetter = 0;
        }
        m_lightOffDelay.set_milliseconds(pause_time);
        m_lightOffDelay.start();
    }

    if (m_lightOffDelay.started()) {
        if (!m_lightOffDelay.elapsed()) {
            return;
        }
        //has elapsed
        m_lightOffDelay.restart();
    }

    char* current = m_mapping[m_random_words[m_currentLetter]];

    digitalWrite(m_led, HIGH);
    if (current[m_currentChar] == '0') {
        m_lightOnDelay.set_milliseconds(m_dot_delay);
    } else {
        m_lightOnDelay.set_milliseconds(m_dash_delay);
    }
    m_lightOnDelay.start();
    if (++m_currentChar == strlen(current)) {
        m_currentChar = 0;
        m_currentLetter++;
    }
}

void light_digit() {
    digitalWrite(m_OA1, HIGH);
    delay(3);
    for(int i = 2; i < 10; i++){
      if(i != 3 && i != 7){
       digitalWrite(i, HIGH);
      }
   }
   digitalWrite(A2,HIGH);
}

int read_input() {
    int t = analogRead(m_potentiometer);
    t = map(t, 0, 1020, 0, 15);

    write_digit(t, m_indicator_pins);
    light_digit();

    if (!digitalRead(buttonPin)) {
        if (t == m_num_to_display) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

void setupMorseCode() {
    pinMode(m_potentiometer, INPUT);
    pinMode(buttonPin, INPUT);

    for (int i = 0; i < 7; i++) {
        pinMode(m_indicator_pins[i], OUTPUT);
        digitalWrite(m_indicator_pins, HIGH);
    }

    pinMode(m_OA1, OUTPUT);
    digitalWrite(m_OA1, LOW);
    digitalWrite(m_led, LOW);

}

int tickMorseCode() {
    show_morse();
    return read_input();
}

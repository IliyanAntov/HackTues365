#ifndef TIMER_H__
#define TIMER_H__

#include "Delay.h"
#include "sevenSegment.h"

int t_pins[] = {2, 3, 4, 5, 6, 7, 8};
int t_OA[] = {9, 10, 11};

int t_seconds = 60;
int t_minutes = 9;
int t_digits[3];

Delay oneSecondDelay;

void setupTimer() {
    oneSecondDelay.set_milliseconds(1000);
    for (int i = 0; i < 8; i++) {
        pinMode(t_pins[i], OUTPUT);
        digitalWrite(t_pins[i], HIGH);
    }
    for (int i = 0; i < 3; i++) {
        pinMode(t_OA[i], OUTPUT);
        digitalWrite(t_OA[i], LOW);
    }
}

void flushIndicator() {
    for (int i = 0; i < 8; i++) {
        digitalWrite(t_pins[i], HIGH);
    }
}

void light_digits() {
     for (int i = 0; i < 3; i++) {
         write_digit(t_digits[i], t_pins);
         digitalWrite(t_OA[i], HIGH);
         delay(5);
         digitalWrite(t_OA[i], LOW);
         flushIndicator();
     }
}

int tickTimer() {
    if (t_minutes == 0 && t_seconds == 0) {
        return -1;
    }

    //Serial.print(t_seconds);
    if (!oneSecondDelay.started()) {
        oneSecondDelay.start();
    }

    if (oneSecondDelay.elapsed()) {
        if (t_seconds > 0) {
            t_seconds--;
        } else {
            if (t_minutes > 0) {
                t_minutes--;
            } else {
                t_minutes = 3;
            }
            t_seconds = 59;
        }
        t_digits[2] = t_minutes;
        t_digits[1] = t_seconds/10;
        t_digits[0] = t_seconds%10;
        oneSecondDelay.restart();
    }
    light_digits();
    return 1;
}

int* getTime() {
    int time[] = {t_minutes,t_seconds};
    return time;
}

#endif

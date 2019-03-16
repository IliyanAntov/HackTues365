#include "Delay.h"
#include "sevenSegment.h"

int t_pins[] = {2, 3, 4, 5, 6, 7, 8};
int t_OA1 = 9;
int t_OA2 = 10;
int t_OA3 = 11;

int t_seconds = 20;
int t_minutes = 0;
int t_digits[3];
unsigned long t_time = millis();

void setupTimer(){
    for (int i = 2; i < 9; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }

    pinMode(t_OA1, OUTPUT);
    digitalWrite(t_OA1, LOW);
    pinMode(t_OA2, OUTPUT);
    digitalWrite(t_OA2, LOW);
    pinMode(t_OA3, OUTPUT);
    digitalWrite(t_OA3, LOW);
}


void light_t_digits(int num){
     digitalWrite(t_OA3, LOW);
     digitalWrite(t_OA2, LOW);
     digitalWrite(t_OA1, LOW);
     if(num == 0){
         digitalWrite(t_OA1, HIGH);
     }
     else if(num == 1){
         digitalWrite(t_OA2, HIGH);
     }
     else{
        digitalWrite(t_OA3, HIGH);
     }
     delay(3);
     for(int i = 2; i < 9; i++){
         digitalWrite(i, HIGH);
     }
}

int tickTimer(){

    if(t_minutes == 0 && t_seconds == 0){
        return -1;
    }

    if(t_seconds > 0){
        t_seconds--;
    } else {
        if (t_minutes > 0) {
            t_minutes--;
        } else {
            t_minutes = 3;
        }
        t_seconds = 59;
    }
    t_time = millis();
    t_digits[2] = t_minutes;
    t_digits[1] = t_seconds/10;
    t_digits[0] = t_seconds%10;

    while (millis() - t_time < 1000) {
        for (int i = 0; i < 3; i++) {

            write_digit(t_digits[i], t_pins);
            light_t_digits(i);
        }
    }

    return 0;
}



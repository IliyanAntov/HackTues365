#include "Delay.h"
#include "sevenSegment.h"

int t_pins[] = {2, 3, 4, 5, 6, 7, 8};
int t_OA1 = 9;
int t_OA2 = 10;
int t_OA3 = 11;

void setup() {
 for (int i = 2; i < 9; i++) {
   pinMode(i, OUTPUT);
   digitalWrite(i, HIGH);
 }

 pinMode(t_OA1, OUTPUT);
 digitalWrite(t_OA1, LOW);
 pinMode(t_OA2, OUTPUT);
 digitalWrite(t_OA2, LOW);
}

int number = 60;
int minutes = 3;
int digits[3];
unsigned long time = millis();

void loop() {
    if(number > 0){
        number--;
    } else {
        if (minutes > 0) {
            minutes--;
        } else {
            minutes = 3;
        }
        number = 59;
    }
    time = millis();
    digits[2] = minutes;
    digits[1] = number/10;
    digits[0] = number%10;

    while (millis() - time < 1000) {
        for (int i = 0; i < 3; i++) {

            write_digit(digits[i], t_pins);
            light_digits(i);
        }
    }
}

void light_digits(int num){
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

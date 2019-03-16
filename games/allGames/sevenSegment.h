#ifndef SEVENSEGMENT_H__
#define SEVENSEGMENT_H__

char segment_numbers[10][8] = {
              "abcdef",
              "bc",
              "abged",
              "abcgd",
              "bcgf",
              "afgcd",
              "afedcg",
              "abc",
              "abcdefg",
              "gfabcd"
          };

void write_digit(int num, int pins[7]) {
    char* number_str = segment_numbers[num];
    for(int j = 0; j < strlen(number_str); j++){
        char letter = number_str[j];
        switch (letter) {
            case 'a':
               digitalWrite(pins[0], LOW);
               break;
            case 'b':
               digitalWrite(pins[1], LOW);
               break;
            case 'c':
               digitalWrite(pins[2], LOW);
               break;
            case 'd':
               digitalWrite(pins[3], LOW);
               break;
            case 'e':
               digitalWrite(pins[4], LOW);
               break;
            case 'f':
               digitalWrite(pins[5], LOW);
               break;
            case 'g':
               digitalWrite(pins[6], LOW);
               break;
        }
    }
}

#endif

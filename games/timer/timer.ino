int OK1 = 10;
int OK2 = 11;
int OK3 = 12;
int aPin = 2;
int bPin = 3;
int cPin = 4;
int dPin = 5;
int ePin = 6;
int fPin = 7;
int gPin = 8;

void setup()
{
  for(int i = 2; i < 9; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  
  pinMode(OK1, OUTPUT);
  digitalWrite(OK1, LOW);
  pinMode(OK2, OUTPUT);
  digitalWrite(OK2, LOW);

  Serial.begin(9600);
  
}

char Numbers[10][8] = {
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

int number = 60;
int minutes = 3;
int digits[3];
unsigned long time = millis();

void loop()
{
  if(number > 0){
    number--;
  }
  else{
    if(minutes > 0){
      minutes--;
    }
    else{
      minutes = 3;
    }
    number = 59;
  }
  time = millis();
  digits[2] = minutes;
  digits[1] = number/10;
  digits[0] = number%10;
  
  while(millis() - time < 1000){
    for(int i = 0; i < 3; i++){
      write_digit(Numbers[digits[i]]);
      light_digit(i);
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

void light_digit(int num){
      digitalWrite(OK3, LOW);
      digitalWrite(OK2, LOW);
      digitalWrite(OK1, LOW);
      if(num == 0){
        digitalWrite(OK1, HIGH);
      }
      else if(num == 1){
        digitalWrite(OK2, HIGH);  
      }
      else{
        digitalWrite(OK3, HIGH);
      }
      delay(3);
      for(int i = 2; i < 9; i++){
         digitalWrite(i, HIGH);
       }
  
}

int timeToPress = 3;
char colors[4] = {'R','G','B','Y'};
int buttonPin = 3;
int common_cathode = 10;
int red_anode = 11;
int green_anode = 12;
int blue_anode = 13;

int fakeTimer = 3;

int buttonState = 1;

void setup() {
  randomSeed(analogRead(0));
  pinMode(buttonPin,INPUT);
  for(int i = 10;i<14;i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  buttonGame();
}

void buttonGame(){
  if(!digitalRead(buttonPin) && buttonState == 1){
    buttonState = -1;
    if(fakeTimer == timeToPress){
      //right moment
      int index = random(4);
      char color = colors[index];
      while(buttonState == -1){
        lightRGB(color);
        //Serial.println(color);
        if(digitalRead(buttonPin)){
          buttonState = 1;
          turnOffRGB();
          if(fakeTimer == timeToPress){
            Serial.println("Game success");
          }else{
            Serial.println("Strike 2");
          }
        }
      }
    }else{
      turnOffRGB();
    }
  }
}

void lightRGB(char color){
  switch(color){
    case 'R':
      digitalWrite(red_anode,HIGH);
      digitalWrite(green_anode,LOW);
      digitalWrite(blue_anode,LOW);
      digitalWrite(common_cathode,LOW);
      break;
    case 'G':
      digitalWrite(red_anode,LOW);
      digitalWrite(green_anode,HIGH);
      digitalWrite(blue_anode,LOW);
      digitalWrite(common_cathode,LOW);
      break;
    case 'B':
      digitalWrite(red_anode,LOW);
      digitalWrite(green_anode,LOW);
      digitalWrite(blue_anode,HIGH);
      digitalWrite(common_cathode,LOW);
      break;
    case 'Y':
      digitalWrite(red_anode,HIGH);
      digitalWrite(green_anode,HIGH);
      digitalWrite(blue_anode,LOW);
      digitalWrite(common_cathode,LOW);
      break;
  }
}

void turnOffRGB(){
  digitalWrite(red_anode,LOW);
  digitalWrite(green_anode,LOW);
  digitalWrite(blue_anode,LOW);
  digitalWrite(common_cathode,HIGH);
}

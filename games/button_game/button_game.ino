int timeToPress = 3;
int colors[4] = {1,2,3,4};
int buttonPin = 2;
int common_anode = 10;
int red_cathode = 11;
int green_cathode = 12;
int blue_cathode = 13;



int fakeTimer = 3;

void setup() {
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
  if(digitalRead(buttonPin)){
    if(fakeTimer == timeToPress){
      //right moment
      Serial.println("Nz");
      lightRGB();
      int color = colors[random(4)];
      int fakeTimer2 = color; //for testing
      Serial.println(color);
      if(!digitalRead(buttonPin)){
        if(color == fakeTimer2){
          Serial.println("Game success");
        }else{
          Serial.println("Strike 2");
        }
      }
    }else{
      Serial.println("strike");
    }
  }
}

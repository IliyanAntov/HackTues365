int b_num_to_display = 3;
char colors[4] = {'R','G','B','Y'};
int b_buttonPin = 3;
int b_common_cathode = 10;
int b_red_anode = 11;
int b_green_anode = 12;
int b_blue_anode = 13;

int fakeTimer = 3;

int b_buttonState = 1;


void turnOnRGB(int R, int G, int B){
  digitalWrite(b_red_anode,R);
  digitalWrite(b_green_anode,G);
  digitalWrite(b_blue_anode,B);
  digitalWrite(b_common_cathode,LOW);
}

void turnOffRGB(){
  digitalWrite(b_red_anode,LOW);
  digitalWrite(b_green_anode,LOW);
  digitalWrite(b_blue_anode,LOW);
  digitalWrite(b_common_cathode,HIGH);
}

void lightRGB(char color) {
  switch(color){
    case 'R':
      turnOnRGB(1,0,0);
      break;
    case 'G':
      turnOnRGB(0,1,0);
      break;
    case 'B':
      turnOnRGB(0,0,1);
      break;
    case 'Y':
      turnOnRGB(1,1,0);
      break;
  }
}

int tickButtonGame() {
    if (!digitalRead(b_buttonPin) && b_buttonState == 1) {
        b_buttonState = -1;
        if (fakeTimer == b_num_to_display) {
            //right moment
            int index = random(4);
            char color = colors[index];
            while (b_buttonState == -1) {
                lightRGB(color);
                if (digitalRead(b_buttonPin)) {
                    b_buttonState = 1;
                    turnOffRGB();
                    if (fakeTimer == b_num_to_display) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            }
        } else {
            turnOffRGB();
            return -1;
        }
    }
    return 0;
}

void setupButtonGame(){
    randomSeed(analogRead(0));
    pinMode(b_buttonPin,INPUT);
    for (int i = 10; i < 14; i++) {
        pinMode(i,OUTPUT);
    }
    turnOffRGB();
}

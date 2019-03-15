//dot - 0
//dash - 1
//hardcode incoming
// | | |
// v v v

char morse_code_mapping[3][10] = {
  "01", //A -> .-
  "1000", //B -> -...
  "1010" //C -> -.-.
};



char input_word[3] = {'A','B','C'};
int num_to_display = 5;

int potentiometer = A0;
int led = 7;

int dot_delay = 300;
int dash_delay = 700;
int pause_btw_words = 800;
int pause_btw_reset = 1000;

void setup() {
  pinMode(potentiometer,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  show_morse();
}

void show_morse(){
  for(int i = 0;i<3;i++){
    //words
    size_t symbol_size = sizeof(morse_code_mapping[i])/sizeof(char); //CHECK IF THE SIZE CALCULATION IS RIGHT
    Serial.println(symbol_size);
    for(int j = 0;j<symbol_size;j++){
      if(morse_code_mapping[i][j] == '0'){
        //dot
        morse_symbol(dot_delay);
      }else if(morse_code_mapping[i][j] == '1'){
        //dash
        morse_symbol(dash_delay);
      }
    }
    delay(pause_btw_words);
  }
  delay(pause_btw_reset);
}

//morse_symbol(dot_delay) - dot
//morse_symbol(dash_delay) - dash

void morse_symbol(int delay_time){
  digitalWrite(led,HIGH);
  delay(delay_time);
  digitalWrite(led,LOW);
  delay(200);
}

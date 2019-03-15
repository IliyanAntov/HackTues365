//dot - 0
//dash - 1

//hardcode incoming
// | | |
// v v v

char morse_code_mapping[30][5] = {
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



char input_word[3] = {'A','H','I'};
int num_to_display = 5;

int potentiometer = 14;
int led = 7;

int dot_delay = 300;
int dash_delay = 700;
int pause_btw_letters = 1500;
int pause_btw_reset = 3000;

void setup() {
  pinMode(potentiometer,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  show_morse();
  read_input();
}

void show_morse(){
  for(int i = 0;i<3;i++){
    //words
    int letter_index = input_word[i] - 'A';
    //size_t symbol_size = sizeof(morse_code_mapping[i])/sizeof(char); //CHECK IF THE SIZE CALCULATION IS RIGHT
    Serial.println(strlen(morse_code_mapping[letter_index]));
    for(int j = 0;j<strlen(morse_code_mapping[letter_index]);j++){
      if(morse_code_mapping[letter_index][j] == '0'){
        //dot
        morse_symbol(dot_delay);
      }else if(morse_code_mapping[letter_index][j] == '1'){
        //dash
        morse_symbol(dash_delay);
      }
    }
    delay(pause_btw_letters);
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

void read_input(){
  int t = analogRead(potentiometer);
  //Serial.println(t);  
  
}

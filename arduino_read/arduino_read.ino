const int LedPin = 2;
int ledState = 0;
int i = 0;

char input[32];

char RGBColor;
char wantedDigit;
char wordIndex;
char morseCodeWord[3];
char buttonOrder[4];
char sequence[6];

char values[16] = { 'r', '2', '3', 'f', 'o', 'x',  '0', '1', '2', '3', '2', '1', '3', '0', '1', '2'};

void setup() {
  pinMode(LedPin, OUTPUT);
  Serial.begin(9600);
  delay(500);
}

void loop() {
    char receiveVal;

    if (Serial.available() > 0) {
       receiveVal = Serial.read();
       input[i] = receiveVal;
       i++;
       Serial.write('1');
    }

    if (i > 15) {
        RGBColor = input[0];
        wantedDigit = input[1];
        wordIndex = input[2];
        morseCodeWord[0] = input[3];
        morseCodeWord[1] = input[4];
        morseCodeWord[2] = input[5];
        buttonOrder[0] = input[6];
        buttonOrder[1] = input[7];
        buttonOrder[2] = input[8];
        buttonOrder[3] = input[9];
        sequence[0] = input[10];
        sequence[1] = input[11];
        sequence[2] = input[12];
        sequence[3] = input[13];
        sequence[4] = input[14];
        sequence[5] = input[15];
    }

    if (RGBColor == 'r') {
        ledState = 1;
    }

    digitalWrite(LedPin, ledState);
}

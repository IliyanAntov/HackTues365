int lights[4] = {28, 29, 30, 31};
int buttonPins[4] = {32, 33, 34, 35};
int seed[4] = {0, 1, 2, 3};
int index = 0;

Button buttons[4];

void setupSimonSays() {
    for (int i = 0; i < 4; i++) {
        pinMode(lights[i], OUTPUT);
        digitalWrite(lights[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttons[i].setPin(buttonPins[i]);
    }

    Serial.begin(9600);
    lightPattern();
}

int currentButton = 0;
int tickSimonSays() {
     //TODO: put less resistance
    if (currentButton == 0 && index == 0) {
        lightPattern();
    }
    for (int i = 0; i < 4; i++) {
        if (buttons[i].isClicked()) {
            if (checkInput(currentButton)) {
                currentButton++;
            } else {
                index = 0;
                currentButton = 0;
                return -1;
            }

            if (currentButton > index) {
                index++;
                currentButton = 0;
                lightPattern();
            }
        }
    }
    return 0;
}

void lightPattern() {
    for (int i = 0; i < index+1; i++) {
        digitalWrite(lights[seed[i]], HIGH);
        delay(100);
        digitalWrite(lights[seed[i]], LOW);
        delay(100);
    }
}

bool checkInput(int current) {
    return !(digitalRead(buttonPins[seed[current]]));
}

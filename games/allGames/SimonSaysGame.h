int lights[4] = {28, 29, 30, 31};
int buttonPins[4] = {32, 33, 34, 35};
int *seed;
int index = 0;

Button *buttons;
Delay lightOn;

void setupSimonSays(int *btns, int* lights) {
    for (int i = 0; i < 4; i++) {
        pinMode(lights[i], OUTPUT);
        digitalWrite(lights[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttons[i].setPin(buttonPins[i]);
    }

    lightPattern();

    buttons = btns;
    seed = lights;

    lightOn.set_milliseconds(100);
}

int currentButton = 0;
bool lightOn = false;
int tickSimonSaysGame() {
     //TODO: put less resistance
    if (currentButton == 0 && index == 0) {
        lightOn = true;
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
                lightOn = true;
            }
        }
    }

    if (lightOn) {
        lightPattern();
    }

    return 0;
}

int currentLed = 0;
void lightPattern() {
    if (currentLed < index+1) {
        digitalWrite(lights[seed[i]], HIGH);
        delay(100);
        digitalWrite(lights[seed[i]], LOW);
        delay(100);
    } else {
        lightOff = false;
    }
}

bool checkInput(int current) {
    return !(digitalRead(buttonPins[seed[current]]));
}

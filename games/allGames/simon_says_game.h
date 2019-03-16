int lights[4] = {2, 3, 4, 5};
int buttonPins[4] = {6, 7, 8, 9};
int seed[4] = {0, 1, 2, 3};
int index = 0;

class Button {
    int pin_;
    int pastState_;
    int current_;
public:
    void setPin(int pin) {
        pin_ = pin;
        pastState_ = digitalRead(pin_);
        current_ = digitalRead(pin_);
    }

    bool isClicked() {
        delay(40);
        pastState_ = current_;
        current_ = digitalRead(pin_);
        if (pastState_ == HIGH) {
            return !current_;
        }
        return false;
    }
};

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

//TODO: add Delay class
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

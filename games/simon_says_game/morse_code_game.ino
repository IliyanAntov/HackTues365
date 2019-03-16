int lights[4] = {2, 3, 4, 5};
int buttonPins[4] = {6, 7, 8, 9};
int seed[4] = {0, 1, 2, 3};
int index = 0;

class Button {
    int pin_;
    int pastState_;
public:
    void setPin(int pin) {
        pin_ = pin;
        pastState_ = digitalRead(pin_);
    }

    void updateState() {
        pastState_ = digitalRead(pin_);
    }

    bool isClicked() {
        if (pastState_ == HIGH) {
            return !digitalRead(pin_);
        }
        return false;
    }
};

Button buttons[4];

void setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(lights[i], OUTPUT);
        digitalWrite(lights[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT);
        buttons[i].setPin(buttonPins[i]);
    }

    Serial.begin(9600);
    lightPattern();
}

int currentButton = 0;
void loop() {
  Serial.println(digitalRead(6));
    for (int i = 0; i < 4; i++) {
        if (buttons[i].isClicked()) {
            Serial.println("cuk");
            if (!checkInput(currentButton)) {
                index = 0;
                lightPattern();
            }

            if (currentButton == index) {
                index++;
                currentButton = 0;
                lightPattern();
            }
        }
        buttons[i].updateState();
    }
}

//TODO: add Delay class
void lightPattern() {
    for (int i = 0; i < index+1; i++) {
        digitalWrite(lights[seed[i]], HIGH);
        delay(500);
        digitalWrite(lights[seed[i]], LOW);
    }
}

bool checkInput(int current) {
    return (digitalRead(buttonPins[seed[current]]));
}

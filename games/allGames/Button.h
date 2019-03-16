#ifndef BUTTON_H__
#define BUTTON_H__

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

#endif

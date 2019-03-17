#ifndef BUTTON_H__
#define BUTTON_H__

#include "Delay.h"

class Button {
    int pin_;
    int pastState_;
    int current_;
    Delay bounceDelay;
public:
    void setPin(int pin) {
        pin_ = pin;
        pastState_ = digitalRead(pin_);
        current_ = digitalRead(pin_);
        bounceDelay.set_milliseconds(40);
        bounceDelay.start();
    }

    bool isClicked() {
        pastState_ = current_;
        current_ = digitalRead(pin_);
        if (pastState_ == HIGH) {
            return !current_;
        }
        return false;
    }
};

#endif

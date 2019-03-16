#ifndef DELAY_H__
#define DELAY_H__

class Delay {
    int milliseconds_;
    unsigned long start_time_;
    bool started_ = false;
public:

    void set_milliseconds(int milliseconds) {
        milliseconds_ = milliseconds;
    }

    void start() {
        start_time_ = millis();
        started_ = true;
    }

    void restart() {
        started_ = false;
    }

    bool elapsed() {
        return millis() - start_time_ >= milliseconds_;
    }

    bool started() {
        return started_;
    }
};

#endif

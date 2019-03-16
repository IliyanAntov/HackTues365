#ifndef GAME_H__
#define GAME_H__

class Game {
    bool done_;
public:
    virtual int tick() = 0; //1 - win 0 - playing -1 - fail
    virtual void setup() = 0;
};

#endif

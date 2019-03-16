#include "Game.h"
#include "MorseCodeGame.h"

Game* games;

void setup() {
    games[0] = new MorseCodeGame();
}

void loop() {
    for (int i = 0; i < 1; i++) {
        int res = games[i]->tick();
        if (res == -1) {
            // wrong answer
        } else if (res == 1) {
            // games[i].done()
        }
    }
}

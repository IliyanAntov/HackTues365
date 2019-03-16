#include "Game.h"
#include "MorseCodeGame.h"
#include "ButtonGame.h"

<<<<<<< HEAD
Game* games;
=======
Game *game;
>>>>>>> 2072a5df47161840f4e5d7fd309b1a3e18922498

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

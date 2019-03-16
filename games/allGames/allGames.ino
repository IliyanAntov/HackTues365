#include "Game.h"
#include "MorseCodeGame.h"

Game* games[1];

void setup() {
    games[0] = malloc(MorseCodeGame());
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

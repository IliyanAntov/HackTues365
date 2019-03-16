#include "Game.h"
#include "MorseCodeGame.h"

Game* games[1];

void setup() {
    games[0] = new MorseCodeGame();
}

void loop() {
    for (int i = 0; i < 1; i++) {
        if (games[i].tick() == -1) {
            // wrong answer
        } else if (games[i] == 1) {
            // games[i].done()
        }
    }
}

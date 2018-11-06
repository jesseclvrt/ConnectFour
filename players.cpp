// Jesse Calvert
// 11.5.2018

#include "players.h"
#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player() {}
Player::~Player() {}

HumanPlayer::HumanPlayer() {}
HumanPlayer::~HumanPlayer() {}

int HumanPlayer::getNextTurn(Game& g) {
    int pick = -1;
    std::cin >> pick;
    return pick;
}

AiPlayer::AiPlayer() { srand(time(NULL)); } // seed RNG
AiPlayer::~AiPlayer() {}

int AiPlayer::getNextTurn(Game& g) {
    bool validPick = false;
    int pick = -1;
    while (!validPick) {
        pick = rand() % g.BoardWidth;
        if (g(pick, 0) == Empty)
            validPick = true;
    }
    std::cout << pick << "\n";
    return pick;
}
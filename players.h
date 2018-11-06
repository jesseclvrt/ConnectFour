// Jesse Calvert
// 11.5.2018

// Classes for types of playable characters

#ifndef PLAYERS_H
#define PLAYERS_H
#include "game.h"

class Game;

class Player {

public:

    Player();
    virtual ~Player();
    virtual int getNextTurn(Game& g) = 0;

};

class HumanPlayer : public Player {

public:

    HumanPlayer();
    ~HumanPlayer();
    int getNextTurn(Game& g);

};

class AiPlayer : public Player {

public:

    AiPlayer();
    ~AiPlayer();
    int getNextTurn(Game& g);

};
#endif
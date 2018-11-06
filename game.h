// Jesse Calvert
// 11.5.2018

// Class for game logic and board

#ifndef GAME_H
#define GAME_H
#include "players.h"

enum GameState {TurnP1, TurnP2, P1Won, P2Won, Draw};
enum BoardField {Player1, Player2, Empty};

class Player;

class Game {

public:

    Game(Player& p1, Player& p2);
    ~Game();

    GameState getState();
    bool isRunning();
    BoardField operator()(int x, int y) const;
    void nextTurn();

    const int BoardWidth = 7;
    const int BoardHeight = 6;

private:

    bool placeToken(int col, BoardField f);
    GameState newState();
    bool isWinner();
    
    BoardField** board;
    GameState state;
    Player& p1;
    Player& p2;

};
#endif
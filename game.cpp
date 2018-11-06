// Jesse Calvert
// 11.5.2018

#include "game.h"
#include "players.h"

Game::Game(Player& p1, Player& p2) 
: state(TurnP1), p1(p1), p2(p2) {
    board = new BoardField*[BoardWidth];
    for (int i = 0; i < BoardWidth; i++)
        board[i] = new BoardField[BoardHeight];
    for (int i = 0; i < BoardWidth; i++)
        for (int j = 0; j < BoardHeight; j++)
            board[i][j] = Empty;
}

Game::~Game() {
    for (int i = 0; i < BoardWidth; i++)
        delete[] board[i];
    delete[] board;
}

GameState Game::getState() {
    return state;
}

bool Game::isRunning() {
    if (state == TurnP1 || state == TurnP2)
        return true;
    return false;
}

BoardField Game::operator()(int x, int y) const {
    if (x < 0 || x > BoardWidth || y < 0 || y > BoardHeight)
        return Empty;
    return board[x][y];
}

void Game::nextTurn() {
    int pick;
    switch (state) {
        case (TurnP1):
            pick = p1.getNextTurn(*this); //board breaks here!
            if (!placeToken(pick - 1, Player1))
                return; // invalid turn
            break;
       case (TurnP2):
            pick = p2.getNextTurn(*this);
            if (!placeToken(pick - 1, Player2))
                return; // invalid turn
            break;
   }
   state = newState();
}

// Returns true if placement worked. Otherwise returns false.
bool Game::placeToken(int col, BoardField f) {
    if (col >= BoardWidth || col < 0 || board[col][0] != Empty)
        return false;
    int i = 0;
    while (i < BoardHeight && board[col][i] == Empty)
        i++;
    board[col][i - 1] = f;
    return true;
}

GameState Game::newState() {
    if (isWinner()) {
        switch (state) {
            case (TurnP1) : return P1Won;
            case (TurnP2) : return P2Won;
        }
    }
    for (int i = 0; i < BoardWidth; i++) { //check draw
        if (board[i][0] == Empty)
            break;
        if (i == BoardWidth - 1)
            return Draw;
    }
    // next player's turn
    switch (state) {
        case (TurnP1) : return TurnP2;
        case (TurnP2) : return TurnP1;
    }
}

bool Game::isWinner() {
    BoardField player;
    state == TurnP1 ? player = Player1 : player = Player2;

    // horizontal
    for (int j = 0; j < BoardHeight - 3; j++)
        for (int i = 0; i < BoardWidth; i++)
            if (board[i][j] == player && board[i][j + 1] == player
                    && board[i][j + 2] == player && board[i][j + 3] == player)
                return true;

    // vertical
    for (int i = 0; i < BoardWidth - 3; i++ )
        for (int j = 0; j < BoardHeight; j++)
            if (board[i][j] == player && board[i + 1][j] == player 
                    && board[i + 2][j] == player && board[i + 3][j] == player)
                return true;


    // ascending diagonal
    for (int i = 3; i < BoardWidth; i++)
        for (int j = 0; j < BoardHeight - 3; j++)
            if (board[i][j] == player && board[i - 1][j + 1] == player 
                    && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
                return true;


    // descending diagonal
    for (int i = 3; i < BoardWidth; i++){
        for (int j = 3; j < BoardHeight; j++){
            if (board[i][j] == player && board[i - 1][j - 1] == player
                    && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player)
                return true;
        }
    }
    return false;
}
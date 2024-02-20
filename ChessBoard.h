#pragma once

#include <SDL2/SDL.h>
#include "Game.h"

class ChessBoard{

public:
    ChessBoard();
    ChessBoard(int);
    ~ChessBoard();
    /*
    render a Board
    */
    void initBoard();
    SDL_Rect* square[64];
    SDL_Color color[3];
private:

int size;

};

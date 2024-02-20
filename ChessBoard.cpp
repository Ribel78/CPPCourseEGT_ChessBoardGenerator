#include "ChessBoard.h"

ChessBoard::ChessBoard(){}

ChessBoard::ChessBoard(int s){
    size = s;
    color[0] = {0,0,0, 255};
    color[1] = {255,255,255,255};
    color[2] = {100, 255, 255, 100};

    for (int i = 0; i < 64; i++){
        square[i] = new SDL_Rect{0, 0, 0, 0};
    }
}

ChessBoard::~ChessBoard(){
    for (int i = 0; i < 64; i++){
        delete square[i];
    }
}

//return chess board - update squares positions
void ChessBoard::initBoard(){
    for (int i = 0; i < 64; i++){
        square[i]->x = i % 8;
        square[i]->y = i / 8;
        square[i]->w = square[i]->h = size / 8;

    }

}
#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the rook piece
_x, _y - attacking piece positions
_piece - the attacking rook ('r' or 'R')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the rook (make sure it is either 'r' or 'R') from the _boardDescription at position x,y as attacking piece
else puts the desired color rook at position x, y 
*/
void rookAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]);

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the bishop piece
_x, _y - attacking piece positions
_piece - the attacking bishop ('b' or 'B')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the bishop (make sure it is either 'b' or 'B') from the _boardDescription at position x,y as attacking piece
else puts the desired color bishop at position x, y 
*/
void bishopAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]);

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the queen piece
_x, _y - attacking piece positions
_piece - the attacking queen ('q' or 'Q')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the queen (make sure it is either 'q' or 'Q') from the _boardDescription at position x,y as attacking piece
else puts the desired color queen at position x, y 
*/
void queenAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]);

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the king piece
_x, _y - attacking piece positions
_piece - the attacking king ('k' or 'K')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the king (make sure it is either 'k' or 'K') from the _boardDescription at position x,y as attacking piece
else puts the desired color king at position x, y 
*/
void kingAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]);

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the pawn piece
_x, _y - attacking piece positions
_piece - the attacking king ('p' or 'P')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the pawn (make sure it is either 'p' or 'P') from the _boardDescription at position x,y as attacking piece
else puts the desired color pawn at position x, y 
*/
void pawnAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]);

/*
_boardDescription - in custom format 
_x, _y - chess piece positions
_piece - chess piece (default = '\0')
Returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the piece from _boardDescription at position x,y
else puts the desired piece at position x, y 
*/
std::string attackSquares(  std::string boardDescription, 
                            int x, int y, char piece = '\0' );
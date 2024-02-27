#include "Utilities.h"



/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the rook piece
_piece - the attacking rook ('r' or 'R')
_x, _y - attacking piece positions
_References to piece descriptions
_is the same piece of opposite color attacked
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the rook (make sure it is either 'r' or 'R') from the _boardDescription at position x,y as attacking piece
else puts the desired color rook at position x, y 
*/
void rookAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]){

        //NO CHECK IF THE attackingPiece is 'r' or 'R' - proceed with CAUTION

        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark init position

        int pos_x = x; int pos_y = y;
        bool isHit = false;
        //sweep up
        while ( !isHit && pos_y > 0 )
        {
            pos_y -= 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'r'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }                       
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'R'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }               
                        isHit = true;
                        break;
                }                
            }
        }
        pos_x = x; pos_y = y;
        isHit = false;
        //sweep down
        while ( !isHit && pos_y < 7 )
        {
            pos_y += 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'r'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'R'){  //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }                 
                        isHit = true;
                        break;
                }                
            }
        }
        //sweep left
        pos_x = x; pos_y = y;
        isHit = false;
        while ( !isHit && pos_x > 0 )
        {
            pos_x -= 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'r'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'R'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        } 
                        isHit = true;
                        break;
                }                
            }
        }  
        //sweep right
        pos_x = x; pos_y = y;
        isHit = false;
        while ( !isHit && pos_x < 7 )
        {
            pos_x += 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){ 
                        if(attackingPiece == 'r'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){ 
                        if(attackingPiece == 'R'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }                 
                        isHit = true;
                        break;
                }                
            }
        }  
}

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
                    char (&blackPieces)[6], char (&whitePieces)[6]){

        //NO CHECK IF THE attackingPiece is 'b' or 'B' - proceed with CAUTION

        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark bishop initial position

        int pos_x = x; int pos_y = y;
        bool isHit = false;
        //sweep left up
        while ( !isHit && ( pos_y > 0 && pos_x > 0 ) )
        {
            pos_y -= 1;
            pos_x -= 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'b'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'B'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }               
                        isHit = true;
                        break;
                }                
            }
        }
        pos_x = x; pos_y = y;
        isHit = false;
        //sweep right up
        while ( !isHit && ( pos_y > 0 && pos_x < 7 ) )
        {
            pos_y -= 1;
            pos_x += 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'b'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'B'){  //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }                 
                        isHit = true;
                        break;
                }                
            }
        }
        //sweep left down
        pos_x = x; pos_y = y;
        isHit = false;
        while ( !isHit && ( pos_y < 7 && pos_x > 0 ) )
        {
            pos_y += 1;
            pos_x -= 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){
                        if(attackingPiece == 'b'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){
                        if(attackingPiece == 'B'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        } 
                        isHit = true;
                        break;
                }                
            }
        }  
        //sweep right down
        pos_x = x; pos_y = y;
        isHit = false;
        while ( !isHit && ( pos_y < 7 && pos_x < 7 ) )
        {
            pos_y += 1;
            pos_x += 1;
            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                    boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
            }

            for (char w_piece : whitePieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){ 
                        if(attackingPiece == 'b'){ //store the attacked white piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                        }
                        isHit = true;
                        break;
                }                
            }
            for (char b_piece : blackPieces){
                if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){ 
                        if(attackingPiece == 'B'){ //store the attacked black piece and end while
                            boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                        }                 
                        isHit = true;
                        break;
                }                
            }
        }  
}

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the queen piece
_x, _y - attacking piece positions
_piece - the attacking queen ('q' or 'Q')
_&isOpposite - returns true if opposite of same kind is attacked
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the queen (make sure it is either 'q' or 'Q') from the _boardDescription at position x,y as attacking piece
else puts the desired color queen at position x, y 
*/
void queenAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]){

        //NO CHECK IF THE attackingPiece is 'q' or 'Q' - proceed with CAUTION

        if(attackingPiece == 'q'){

            //call rookAttack
            rookAttack ( boardDescription, boardOverlay, 'r', x, y, blackPieces, whitePieces );

            //call bishopAttack
            bishopAttack ( boardDescription, boardOverlay, 'b', x, y, blackPieces, whitePieces );
        }

        if(attackingPiece == 'Q'){

            //call rookAttack
            rookAttack ( boardDescription, boardOverlay, 'R', x, y, blackPieces, whitePieces );

            //call bishopAttack        
            bishopAttack ( boardDescription, boardOverlay, 'B', x, y, blackPieces, whitePieces );

        }
        
        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark queen initial position 
}

/*
_boardDescription - chess board description in custom format 
_boardOverlay - chess board description to update attack positions of the knight piece
_x, _y - attacking piece positions
_piece - the attacking knight ('n' or 'N')
returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the knight (make sure it is either 'n' or 'N') from the _boardDescription at position x,y as attacking piece
else puts the desired color knight at position x, y 
*/
void knightAttack (   std::string &boardDescription, 
                    std::string &boardOverlay, 
                    char attackingPiece, 
                    int x, int y, 
                    char (&blackPieces)[6], char (&whitePieces)[6]){
        //NO CHECK IF THE attackingPiece is 'n' or 'N' - proceed with CAUTION
        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark bishop initial position

        int pos_x = x; int pos_y = y;
        bool isHit = false;
        //turn
        int knight_point_x[] = {1, 2, 2, 1, -1, -2, -2, -1};
        int knight_point_y[] = {2, 1, -1, -2, -2, -1, 1, 2};
        for (int p = 0; p < 8; p++){
            pos_y = y + knight_point_y[p];
            pos_x = x + knight_point_x[p];            
            if(( pos_y >= 0 && pos_y <= 7 ) && ( pos_x >= 0 && pos_x <= 7 )){    
                if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                        boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                }      
                for (char w_piece : whitePieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){ 
                            if(attackingPiece == 'n'){ //store the attacked white piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                            }
                    }                
                }
                for (char b_piece : blackPieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){ 
                            if(attackingPiece == 'N'){ //store the attacked black piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                            }
                    }
                }
            }
        }                                
}

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
                    char (&blackPieces)[6], char (&whitePieces)[6]){
        //NO CHECK IF THE attackingPiece is 'n' or 'N' - proceed with CAUTION
        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark bishop initial position

        int pos_x = x; int pos_y = y;
        bool isHit = false;
        //turn
        int king_point_x[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int king_point_y[] = {1, 1, 0, -1, -1, -1, 0, 1};
        for (int p = 0; p < 8; p++){
            pos_y = y + king_point_y[p];
            pos_x = x + king_point_x[p];            
            if(( pos_y >= 0 && pos_y <= 7 ) && ( pos_x >= 0 && pos_x <= 7 )){    
                if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                        boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                }      
                for (char w_piece : whitePieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){ 
                            if(attackingPiece == 'k'){ //store the attacked white piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                            }
                    }                
                }
                for (char b_piece : blackPieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){ 
                            if(attackingPiece == 'K'){ //store the attacked black piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                            }
                    } 
                }
            }  
        }                           
}

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
                    char (&blackPieces)[6], char (&whitePieces)[6]){
        //NO CHECK IF THE attackingPiece is 'n' or 'N' - proceed with CAUTION
        boardOverlay[ (y * 8) + x ] = attackingPiece; //mark bishop initial position

        int pos_x = x; int pos_y = y;

        //attack
        int pawn_point_x[] = {-1, 1};
        for (int p = 0; p < 2; p++){
            pos_y = y + ( ( attackingPiece == 'p') ? 1 : -1 );
            pos_x = x + pawn_point_x[p];
            if(( pos_y >= 0 && pos_y <= 7 ) && ( pos_x >= 0 && pos_x <= 7 )){    
                for (char w_piece : whitePieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == w_piece){ 
                            if(attackingPiece == 'p'){ //store the attacked white piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = w_piece;
                            }
                    }                
                }
                for (char b_piece : blackPieces){
                    if ( boardDescription[ (pos_y * 8) + pos_x ] == b_piece){ 
                            if(attackingPiece == 'P'){ //store the attacked black piece and end while
                                boardOverlay[ (pos_y * 8) + pos_x ] = b_piece;
                            }  
                    } 
                }
            }  
        }    
        //move
        pos_x = x;
        pos_y = y;  
        if (attackingPiece == 'p'){
                pos_y += 1;
                if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                        boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                        if (y == 1){
                            pos_y += 1;
                            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                                boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                            }                    
                        }     
                }
    
        }
        pos_y = y;
        if (attackingPiece == 'P'){
                pos_y -= 1;
                if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                        boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                        if (y == 6){
                            pos_y -= 1;
                            if ( boardDescription[ (pos_y * 8) + pos_x ] == '-'){ //empty square on path
                                boardOverlay[ (pos_y * 8) + pos_x ] = 'X';
                            }                    
                        }     
                }
    
        }
}

/*
_boardDescription - in custom format 
_x, _y - chess piece positions
_piece - chess piece (default = '\0')
Returns board with allowed positions ['X'] and attacked pieces of opposite color
if default piece then it takes the piece from _boardDescription at position x,y
else puts the desired piece at position x, y 
*/
std::string attackSquares(  std::string boardDescription, 
                            int x, int y, char piece ){

    char blackPieces[6] = {'k','q','r','b','n','p'};
    char whitePieces[6] = {'K','Q','R','B','N','P'}; 
    //bool bK = bQ = bR = bB = bN = bP = false;
    std::string boardOverlay = ""; //a string to write sequential results in
    for (int i = 0; i < 64; i++){
        boardOverlay.append("-");
    } //fill with empty sqwares '-'

    if(!piece){ //default piece as argument? take the piece with corrds x,y from the board
        piece = boardDescription[(y * 8 + x)]; 
    }
    //black rook
    if (piece == 'r'){
        rookAttack ( boardDescription, boardOverlay, 'r', x, y, blackPieces, whitePieces );
    }
    if (piece == 'R'){
        rookAttack ( boardDescription, boardOverlay, 'R', x, y, blackPieces, whitePieces );
    }    
    if (piece == 'b'){
        bishopAttack ( boardDescription, boardOverlay, 'b', x, y, blackPieces, whitePieces );
    }
    if (piece == 'B'){
        bishopAttack ( boardDescription, boardOverlay, 'B', x, y, blackPieces, whitePieces );
    }
    if (piece == 'q'){
        queenAttack ( boardDescription, boardOverlay, 'q', x, y, blackPieces, whitePieces );
    }
    if (piece == 'Q'){
        queenAttack ( boardDescription, boardOverlay, 'Q', x, y, blackPieces, whitePieces );
    }    
    if (piece == 'n'){
        knightAttack ( boardDescription, boardOverlay, 'n', x, y, blackPieces, whitePieces );
    }
    if (piece == 'N'){
        knightAttack ( boardDescription, boardOverlay, 'N', x, y, blackPieces, whitePieces );
    }  
    if (piece == 'k'){
        kingAttack ( boardDescription, boardOverlay, 'k', x, y, blackPieces, whitePieces );
    }
    if (piece == 'K'){
        kingAttack ( boardDescription, boardOverlay, 'K', x, y, blackPieces, whitePieces );
    } 
    if (piece == 'p'){
        pawnAttack ( boardDescription, boardOverlay, 'p', x, y, blackPieces, whitePieces );
    }
    if (piece == 'P'){
        pawnAttack ( boardDescription, boardOverlay, 'P', x, y, blackPieces, whitePieces );
    }     

    return boardOverlay;
}
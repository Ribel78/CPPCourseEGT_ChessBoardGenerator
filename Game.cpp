//Game.cpp
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <cstring>

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				//SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);//not needed

			}
			else {
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else {
			std::cout << "window init failed\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail\n";
		return false;
	}
	std::cout << "init success\n";
	running = true;
	return true;
}

//chess pieces in uinicode white to black in order King, Queen, Rook, Bishop, Knight, Pawn 
//std::string cp_unicode[12] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
//only black chess characters
std::string cpb_unicode[6] = {"\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
//chess pieces lookup reference according to FEN abbreviations
std::string cp_lookupRef[12] = {"K","Q","R","B","N","P","k","q","r","b","n","p"};

bool Game::ttf_init(){
	if(TTF_Init() == -1){
		return false;
	}
	// loading fonts into pointer variables
	TTF_Font* font1 = TTF_OpenFont("fonts/DejaVuSans.ttf", 72); 
	TTF_Font* font2 = TTF_OpenFont("fonts/segoepr.ttf", 72);

	if(font1 == NULL || font2 == NULL){
		return false;
	}
	//creating temp surface
	SDL_Surface* tempSurfaceText = NULL;

	//create temp surface from font with given text and transfer the pixels to chess pieces textures 
	
	tempSurfaceText = TTF_RenderUTF8_Blended(font1, "White \u2654 \u2655 \u2656 \u2657 \u2658 \u2659 Black \u265A \u265B \u265C \u265D \u265E \u265F", {0,0,0,255});
	chessTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	//Create textures from font chess characters - only the black pieces (6)
	for (int i = 0; i < 12; i++){
		if (i / 6 == 0){ //white first - K, Q, R, B, N, P

			tempSurfaceText = TTF_RenderUTF8_Blended(font1, cpb_unicode[i%6].c_str(), {254, 237, 211, 255});
			chessPieces[i] = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

		} else { //black second - k, q, r, b, n, p
			
			tempSurfaceText = TTF_RenderUTF8_Blended(font1, cpb_unicode[i%6].c_str(), {0 , 0, 0, 255});
			chessPieces[i] = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

		}
	}

	// tempSurfaceText = TTF_RenderUTF8_Blended(font1, "\u265B", {255, 255, 255, 255});
	// chessPiece = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);


	// //use the same temp surface for the next iterrations
	// tempSurfaceText = TTF_RenderText_Blended(font2, "Hello world!", {0,255,255,255});
	// textTextureFont2 = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	// //..this function allows multiline text
	// tempSurfaceText = TTF_RenderText_Blended_Wrapped(font1, "Hello world!\nThis wraps the text.", 
	// 													{255,0,255,255}, 300);
	// textTextureFont1Wrapped = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	// //..
	// tempSurfaceText = TTF_RenderText_Blended_Wrapped(font2, "Hello world!\nThis wraps the text.", 
	// 													{0,0,255,255}, 500);
	// textTextureFont2Wrapped = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	// //..last one - we'll check if clicked on
	// tempSurfaceText = TTF_RenderText_Blended(font1, "CLICK", {255,0,255,255});
	// clickableTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	//query info from a texture and write to variables 
	// int tw, th;
	// SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	// // Game object SDL_Rect - gets the dimensions from the texture for filling later
	// dRectFont1 = {10, 10, tw, th};
	int tw, th;
	SDL_QueryTexture(chessTexture, 0, 0, &tw, &th);
	// Game object SDL_Rect - gets the dimensions from the texture for filling later
	dRectFont1 = {10, 10, tw, th};
	// //..
	// SDL_QueryTexture(textTextureFont2, 0, 0, &tw, &th);
	// dRectFont2 = {10, 320, tw, th};	
	// //..
	// SDL_QueryTexture(textTextureFont1Wrapped, 0, 0, &tw, &th);
	// dRectFont1Wrapped = {650, 10, tw, th};	
	// //..
	// SDL_QueryTexture(textTextureFont2Wrapped, 0, 0, &tw, &th);
	// dRectFont2Wrapped = {650, 320, tw, th};	

	// // - get dimensions for the clickable texture
	// SDL_QueryTexture(clickableTexture, 0, 0, &tw, &th);
	// // get window dimensions
	// int ww, wh;
	// SDL_GetWindowSize(window, &ww, &wh);
	// //SDL_Rect for the clickable text 
	// clickableRect = {ww/2 - tw, wh/2 - th, tw, th};

	SDL_FreeSurface(tempSurfaceText); // delete the temp surface
	TTF_CloseFont(font1); //deleting font pointers
	TTF_CloseFont(font2); //..

	return true;
}

void Game::render() {
	//SDL_RenderClear(renderer); // clear from previous pixels
	//draws in the renderer the portion from the texture (srcRect = NULL if using the whole texture size)
	//SDL_RenderCopy(renderer, chessTexture, NULL, &dRectFont1);

	SDL_RenderCopy(renderer, chessPieces[6], NULL, chess_square[32]);
	// SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
	// SDL_RenderCopy(renderer, textTextureFont2, NULL, &dRectFont2);
	// SDL_RenderCopy(renderer, textTextureFont1Wrapped, NULL, &dRectFont1Wrapped);
	// SDL_RenderCopy(renderer, textTextureFont2Wrapped, NULL, &dRectFont2Wrapped);
	// SDL_RenderCopy(renderer, clickableTexture, NULL, &clickableRect);
	//all drawn - now dispaly
	SDL_RenderPresent(renderer);
}

bool Game::isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r,  int xDown, int yDown, int xUp, int yUp){
	int tw, th;
	// get info about texture dimensions and assign it to variables
	SDL_QueryTexture(t, 0, 0, &tw, &th);

	// checks positions of the mouse when down and up separately and compare against the SDL_Rect positions
	if(((xDown > r->x) && (xDown < r->x +tw)) && ((xUp > r->x) && (xUp < r->x +tw))&&
		((yDown > r->y) && (yDown < r->y +th)) && ((yUp > r->y) && (yUp < r->y +th))){
			//click coordinates inside  SDL_Rect rectangle
			return true;
	}
	//try logic directly with SDL_Rect instead of Texture wifht and heightpliers
	return false;
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: running = false; break;

		case SDL_MOUSEBUTTONDOWN: {
			//int msx, msy;
			//std::cout << "mouse button down\n";
			//if (event.button.button == SDL_BUTTON_LEFT) {
			//	SDL_GetMouseState(&msx, &msy);
			//	std::cout << msx << ":" << msy << "\n";
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				mouseDownX = msx;
				mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP: {
			//int msx, msy;
			//std::cout << "mouse button up\n";
			//if (event.button.button == SDL_BUTTON_RIGHT) {
			//	SDL_GetMouseState(&msx, &msy);
			//	std::cout << msx << ":" << msy << "\n";
			//}
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				std::cout << (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy) ? "CLICKED" : "NOT CLICKED");
				
			}
		}; break;

		case SDL_KEYDOWN:{
			if(event.key.keysym.sym == SDLK_LEFT){
				std::cout << "Left Arrow\n";
				dRectFont1.x--;
			}
			if(event.key.keysym.sym == SDLK_RIGHT){
				dRectFont1.x++;
			}
			if(event.key.keysym.sym == SDLK_UP){
				dRectFont1.y--;
			}
			if(event.key.keysym.sym == SDLK_DOWN){
				dRectFont1.y++;
			}
		}; break;
		case SDL_KEYUP:{
			std::cout << "Key is up\n";
		}; break;
		case SDL_MOUSEMOTION: {
			std::cout << event.motion.x << ":" << event.motion.y << std::endl;
			dRectFont2.x = event.motion.x - dRectFont2.w/2;
			dRectFont2.y = event.motion.y - dRectFont2.h/2;
		}; break;
		default: break;
		}
	}
}

void Game::update() {
	SDL_Delay(100);
}

void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() {
	return Game::running;
}

Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;

	//Chess Board Size and Color
	chess_size = 640;
    chess_color[0] = {214, 187, 141, 255}; //white square
	chess_color[1] = {198, 130, 66, 255}; //black square
    chess_color[2] = {100, 255, 255, 100}; // highlight color

    for (int i = 0; i < 64; i++){
        chess_square[i] = new SDL_Rect{0, 0, 0, 0};
    }

}

Game::~Game() {
	// delete window;
	// delete renderer;

	//Chess
    for (int i = 0; i < 64; i++){
        delete chess_square[i];
    }	
}

//Chess

void Game::initBackground(){
	SDL_SetRenderDrawColor(renderer, 23,138,207, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::initBoard(){
    for (int i = 0; i < 64; i++){
        chess_square[i]->x = (i % 8)*(chess_size / 8);
        chess_square[i]->y = (i / 8)*(chess_size / 8);
        chess_square[i]->w = chess_square[i]->h = chess_size / 8;
    }	
}

void Game::drawBoard(){
	for (int i = 0; i < 64; i++){
		SDL_SetRenderDrawColor(
			renderer,
			chess_color[(i + ( i / 8 ) % 2 ) %2 ].r,
			chess_color[(i + ( i / 8 ) % 2 ) %2].g,
			chess_color[(i + ( i / 8 ) % 2 ) %2].b,
			chess_color[(i + ( i / 8 ) % 2 ) %2].a
		);
		SDL_RenderFillRect(renderer,chess_square[i]);
	}
	//SDL_RenderPresent(renderer);
}

void Game::drawPieces(){
	std::string chessBoardShuffle;
	std::string fenChessBoard;

	shufflePieces(true, chessBoardShuffle, fenChessBoard);

	std::cout << fenChessBoard << std::endl;

	//white pawns
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[48]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[49]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[50]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[51]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[52]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[53]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[54]);
	SDL_RenderCopy(renderer, chessPieces[5], NULL, chess_square[55]);

	//other white 
	SDL_RenderCopy(renderer, chessPieces[2], NULL, chess_square[56]);
	SDL_RenderCopy(renderer, chessPieces[4], NULL, chess_square[57]);
	SDL_RenderCopy(renderer, chessPieces[3], NULL, chess_square[58]);
	SDL_RenderCopy(renderer, chessPieces[1], NULL, chess_square[59]);
	SDL_RenderCopy(renderer, chessPieces[0], NULL, chess_square[60]);
	SDL_RenderCopy(renderer, chessPieces[3], NULL, chess_square[61]);
	SDL_RenderCopy(renderer, chessPieces[4], NULL, chess_square[62]);
	SDL_RenderCopy(renderer, chessPieces[2], NULL, chess_square[63]);

	//black pawns
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[8]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[9]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[10]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[11]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[12]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[13]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[14]);
	SDL_RenderCopy(renderer, chessPieces[11], NULL, chess_square[15]);

	//other black
	SDL_RenderCopy(renderer, chessPieces[8], NULL, chess_square[0]);
	SDL_RenderCopy(renderer, chessPieces[10], NULL, chess_square[1]);
	SDL_RenderCopy(renderer, chessPieces[9], NULL, chess_square[2]);
	SDL_RenderCopy(renderer, chessPieces[7], NULL, chess_square[3]);
	SDL_RenderCopy(renderer, chessPieces[6], NULL, chess_square[4]);
	SDL_RenderCopy(renderer, chessPieces[9], NULL, chess_square[5]);
	SDL_RenderCopy(renderer, chessPieces[10], NULL, chess_square[6]);
	SDL_RenderCopy(renderer, chessPieces[8], NULL, chess_square[7]);

	SDL_RenderPresent(renderer);

}

/*
shuffle a char string of 64 chars formated to FEN chess board description
and assigns raw and parsed char* to external variables
_shuff - to shuffle (1) or keep ordered chess set
_&custDescription - string reference to write the chess board description
_&fenDescription - string reference to write the FEN the chess board description
*/
void Game::shufflePieces(bool shuff, std::string &custDescription, std::string &fenDescription){
	char chess_set[] = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";

	//https://www.chess.com/terms/fen-chess
	char tempFEN[71]; //string to hold the positions including separators '/' (64+7)
	char FEN[71] = {'0',}; //string to hold the pieces including separators in FEN Format

	if (shuff){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine rand_en;
		rand_en.seed(seed);
		//random chess board all with all pieces
		std::shuffle(chess_set, chess_set+64, rand_en); 

		std::string temp(chess_set);
		custDescription = temp;

		int j = 0;
		for (int i = 0; i < 64; i++){
			tempFEN[j] = chess_set[i];
			if( (i+1) % 8 == 0 && (( i+1 ) > 0 && ( i+1 ) < 64)){
				j+=1;
				tempFEN[j] = '/';
			}
			j+=1;
		}

		int empty_space = 0;
		j=0;
		int count = 0;
		while(count < 71)
		{
			if (tempFEN[count] != '-' && empty_space==0){

				FEN[j] = tempFEN[count];
				count += 1;
				j += 1;

			} else if(tempFEN[count] == '-'){

				empty_space += 1;
				FEN[j] = ('0' + empty_space);
				count += 1;

			} else{
				j += 1;
				empty_space = 0;
			}
		}

		temp = std::string(FEN);
		fenDescription = temp;
		} else{
			custDescription = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
			fenDescription = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
		}
}
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
	simulating = false;
	return true;
}

//chess pieces in uinicode white to black in order King, Queen, Rook, Bishop, Knight, Pawn 
//std::string cp_unicode[12] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
//only black chess characters
std::string cpb_unicode[6] = {"\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F"};
//chess pieces lookup reference according to FEN abbreviations
//chess piece look up reference
std::string cp_lookupRef = "KQRBNPkqrbnp";

bool Game::ttf_init(){
	if(TTF_Init() == -1){
		return false;
	}
	// loading fonts into pointer variables
	TTF_Font* font1 = TTF_OpenFont("fonts/DejaVuSans.ttf", 48); //chess pieces
	TTF_Font* font2 = TTF_OpenFont("fonts/segoepr.ttf", 72); // Text

	if(font1 == NULL || font2 == NULL){
		return false;
	}
	//creating temp surface
	SDL_Surface* tempSurfaceText = NULL;

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
	int tw, th; //variables to store dimensions data
	//use the same temp surface for the next iterrations
	tempSurfaceText = TTF_RenderText_Blended(font2, "Chess Board Generator", {0,0,0,255});
	textTitleTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	//SDL_QueryTexture(textTextureFont2, 0, 0, &tw, &th);
	textTitleRect = {680, 20, 560, 64};	

	tempSurfaceText = TTF_RenderText_Blended_Wrapped(font1, "Start\n Simulation", {0,0,0,255}, 0);
	buttonStartTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	buttonStartRect = {680, 560, 256, 64};

	tempSurfaceText = TTF_RenderText_Blended_Wrapped(font1, "Stop\n Simulation", {0,0,0,255}, 0);
	buttonStopTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	buttonStopRect = {980, 560, 256, 64};

	//..this function allows multiline text
	//..
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
	

	SDL_FreeSurface(tempSurfaceText); // delete the temp surface
	TTF_CloseFont(font1); //deleting font pointers
	TTF_CloseFont(font2); //..

	//dynamic text KJFKKF
	infoFont = TTF_OpenFont("fonts/segoepr.ttf", 28); // try updating the text content
	if(infoFont == NULL){
		std::cout << "infoFont not loaded" << std::endl;
	}	
	
	

	return true;
}

void Game::render() {
	//SDL_RenderClear(renderer); // clear from previous pixels
	//draws in the renderer the portion from the texture (srcRect = NULL if using the whole texture size)

	//SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
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
	//try logic directly with SDL_Rect instead of Texture width and height
	return false;
}

bool Game::buttonClicked(SDL_Rect* r,  int xDown, int yDown, int xUp, int yUp){
	//int tw, th;
	// get info about texture dimensions and assign it to variables
	//SDL_QueryTexture(t, 0, 0, &tw, &th);

	// checks positions of the mouse when down and up separately and compare against the SDL_Rect positions
	if(((xDown > r->x) && (xDown < r->x +r->w)) && ((xUp > r->x) && (xUp < r->x +r->w))&&
		((yDown > r->y) && (yDown < r->y +r->h)) && ((yUp > r->y) && (yUp < r->y +r->h))){
			//click coordinates inside  SDL_Rect rectangle
			return true;
	}
	//try logic directly with SDL_Rect instead of Texture width and height
	return false;
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: running = false; break;

		case SDL_MOUSEBUTTONDOWN: {
			// int msx, msy;
			// std::cout << "mouse button down\n";
			// if (event.button.button == SDL_BUTTON_LEFT) {
			// 	SDL_GetMouseState(&msx, &msy);
			// 	std::cout << msx << ":" << msy << "\n";
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				mouseDownX = msx;
				mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP: {
			int msx, msy;
			std::cout << "mouse button up\n";
			if (event.button.button == SDL_BUTTON_RIGHT) {
				SDL_GetMouseState(&msx, &msy);
				std::cout << msx << ":" << msy << "\n";
			}
			//int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				if(buttonClicked(&buttonStartRect,mouseDownX,mouseDownY, msx, msy)){
					setSimulating(true);
				}
				if(buttonClicked(&buttonStopRect,mouseDownX,mouseDownY, msx, msy)){
					setSimulating(false);
				}
			}
		}; break;

		case SDL_KEYDOWN:{
			// if(event.key.keysym.sym == SDLK_LEFT){
			// 	std::cout << "Left Arrow\n";
			// 	dRectFont1.x--;
			// }
			// if(event.key.keysym.sym == SDLK_RIGHT){
			// 	dRectFont1.x++;
			// }
			// if(event.key.keysym.sym == SDLK_UP){
			// 	dRectFont1.y--;
			// }
			// if(event.key.keysym.sym == SDLK_DOWN){
			// 	dRectFont1.y++;
			// }
		}; break;
		case SDL_KEYUP:{
			// std::cout << "Key is up\n";
		}; break;
		case SDL_MOUSEMOTION: {

		}; break;
		default: break;
		}
	}
}

void Game::update() {

	SDL_Delay(250);
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

bool Game::isSimulating() {
	return Game::simulating;
}

void Game::setSimulating(bool state){
	Game::simulating = state;
}

Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
	Game::simulating = false; //simulate chessboard

	//Chess Board Size and Color
	chess_size = 640;
    chess_color[0] = {214, 187, 141, 255}; //"white" square
	chess_color[1] = {198, 130, 66, 255}; //"black" square
    chess_color[2] = {100, 255, 100, 50}; // highlight color

	//simulation time variables
	numberOfSimulations = 0;
	totalSimulationTime = 0;
	averageSimulationTime = 0;
	simulationTime = 0;

    for (int i = 0; i < 64; i++){
        chess_square[i] = new SDL_Rect{0, 0, 0, 0};
    }
	queueCustomSetDescription.push("rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR");
	queueFENSetDescription.push("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

Game::~Game() {
	// delete window;
	// delete renderer;
	//Chess
    for (int i = 0; i < 64; i++){
        delete chess_square[i];
    }	

	//dynamic text KJFKKF
	SDL_FreeSurface(tempSurfaceDynamicText); //closing surface for dynamic text
	TTF_CloseFont(infoFont); // closing font for dynamic text
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

void Game::drawBoardOverlay(){
	bool showOvrlay = false;
	if (showOvrlay){
		for (int i = 0; i < 64; i++){
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, 
				chess_color[2].r, chess_color[2].g, 
				chess_color[2].b, chess_color[2].a);
			SDL_RenderFillRect(renderer,chess_square[i]);
		}
	}
	//SDL_RenderPresent(renderer);	
}

void Game::drawStaticText(){
	// Title
	SDL_RenderCopy(renderer, textTitleTexture, NULL, &textTitleRect);
	SDL_SetRenderDrawColor(renderer, 234,123,53,255);

	// Info - Glitchy - 	//dynamic text KJFKKF
	tempSurfaceDynamicText = TTF_RenderText_Blended(infoFont, 
	queueFENSetDescription.back().c_str(), {0,0,0,255});
	if(tempSurfaceDynamicText == NULL){
		std::cout << "Surface, not created" << std::endl;
	}
	textInfoTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceDynamicText);
	//query info from a texture and write to variables 
	int tw, th;
	SDL_QueryTexture(textInfoTexture, 0, 0, &tw, &th);
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);
	// Game object SDL_Rect - gets the dimensions from the texture for filling later
	infoTextRect = {(ww-tw)/2, 650, tw, th}; // for the textInfoTexture
	SDL_RenderCopy(renderer, textInfoTexture, NULL, &infoTextRect);

	// Buttons
	SDL_RenderFillRect(renderer,&buttonStartRect);
	SDL_RenderCopy(renderer, buttonStartTex, NULL, &buttonStartRect);
	SDL_RenderFillRect(renderer,&buttonStopRect);
	SDL_RenderCopy(renderer, buttonStopTex, NULL, &buttonStopRect);
	//SDL_RenderPresent(renderer);

}

void Game::drawPieces(){
	//Pr2p2R/1p1pP3/P1nPpP1q/2PnK3/1p2br2/p3bBQ1/P2RN1kp/PN3pB1
	//Rp5k/4pqpb/1R4P1/r1p1Pp1n/1r2PQ1P/3NN3/1BPpP2p/bP1BKpnP
	//1q2pP1k/pn1pP1R1/2rP1BNp/3NP1n1/1Pb1bp1P/1K2RP1p/Bp5Q/r1p3P1
	//R2K2p1/3pp1q1/1p2NRPN/Q1bP1P2/2rPpb2/1pnp1p2/2krPBPP/2B1P2n
	//R2K2p1/3pp1q1/1p2NRPN/Q1bP1P2/2rPpb2/1pnp1p2/2krPBPP/2B1P2n
	//std::string chessBoardShuffle = "P2P1Q2/2Pp1r1p/1N2B3/2qbR2P/3p1Pbk/p1NPP1p1/p2R1pPn/2BnrKp1";

	std::string chessBoardShuffle;
	std::string fenChessBoard;

	shufflePieces(isSimulating(), chessBoardShuffle, fenChessBoard);
	//std::cout << fenChessBoard << std::endl;

	for (int i = 0; i < 64; i++){
		if (chessBoardShuffle[i] == '-'){
			continue;
		}
		for (int j = 0; j < 12; j++){
			if (chessBoardShuffle[i] == cp_lookupRef[j]){
				SDL_RenderCopy(renderer, chessPieces[j], NULL, chess_square[i]);
				continue;
			}
		}
	}
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
	//mark single simulation
	int startTime = SDL_GetTicks();

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

		//simulation ends here
		
		simulationTime = SDL_GetTicks() - startTime; // gives zero
		std::cout << startTime << "-" << simulationTime << std::endl;

		// Reenable once simulation time is fixed 
		// numberOfSimulations += 1;
		// totalSimulationTime += simulationTime;
		// averageSimulationTime = totalSimulationTime / numberOfSimulations;

		std::string temp(chess_set);
		custDescription = temp;
		queueCustomSetDescription.push(custDescription);

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
		queueFENSetDescription.push(fenDescription);

		if(queueCustomSetDescription.size()==21){
			queueCustomSetDescription.pop();
			queueFENSetDescription.pop();
		}

		} else{
			// custDescription = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
			// fenDescription = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
			custDescription = queueCustomSetDescription.back();
			fenDescription = queueFENSetDescription.back();
		}
}
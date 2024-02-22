//Game.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <queue>

class Game {
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	bool isSimulating(); //chess 
	void setSimulating(bool); //chess
	bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r,  int xDown, int yDown, int xUp, int yUp);
	bool buttonClicked(SDL_Rect* r,  int xDown, int yDown, int xUp, int yUp);
	//Chess
	void initBackground();
	void initBoard();
	void drawBoard();
	void drawBoardOverlay();	
	void drawStaticText();

	void drawPieces();
	void shufflePieces(bool, std::string&, std::string&);
	
private:

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	bool simulating;
	SDL_Texture	*textTextureFont1, 
				*textTitleTexture, 
				*textTextureFont2Wrapped,
				*chessTexture;
	SDL_Rect 	dRectFont1, 
				textTitleRect, 
				dRectFont2Wrapped;
	SDL_Texture* clickableTexture;
	SDL_Rect clickableRect;
	int mouseDownX, mouseDownY;

	//Chess
	int chess_size;
    SDL_Rect* chess_square[64];
	int boardOverlay[64]; //higlight valid moves
    SDL_Color chess_color[3];	
	SDL_Texture* chessPieces[12];
	SDL_Texture* buttonStartTex;
	SDL_Rect buttonStartRect;
	SDL_Texture* buttonStopTex;
	SDL_Rect buttonStopRect;
	std::queue<std::string> queueCustomSetDescription;
	std::queue<std::string> queueFENSetDescription;

	//dynamic text KJFKKF
	TTF_Font* infoFont; // Update the text content
	SDL_Surface* tempSurfaceDynamicText = NULL; 
	SDL_Texture *textInfoTexture;
	SDL_Rect infoTextRect;

	int numberOfSimulations;
	double totalSimulationTime;
	double averageSimulationTime;
	double simulationTime;

};

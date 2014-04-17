#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Game.h"

#ifndef DEF_WINDOW
#define DEF_WINDOW

	struct Dimension {
		int width = 0;
		int height = 0;
	};
	
	enum Stage {MAIN, INGAME};

	class Window {
		public:
			SDL_Surface *screen, *txt;
			TTF_Font *fontTitle, *fontMenu, *fontStatus;
			SDL_Color white;
			SDL_Rect baseline;
			Dimension window;
			Stage stage;
			SDL_Rect pos;
			Game game;
			
			Window();
			~Window();
			void displayMainScreen();
			void displayInGameScreen();
			void displayGameOver();
			void startNewGame();
			void handleEvents();
			void handleMainKeyStroke(int key);
			void handleInGameKeyStroke(int key);
	};
	
#endif
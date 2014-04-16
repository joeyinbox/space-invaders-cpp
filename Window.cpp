#include <stdio.h>
#include "Window.h"

using namespace std;


/**
 * Initialise all window variables and create a window
 * 
 * @param	none
 * @return	void
 *
 */
Window::Window() {
	// Initialise surfaces
	this->screen = NULL;
	this->txt = NULL;
	this->crab = NULL;
	this->octopus = NULL;
	this->squid = NULL;
	this->spaceship = NULL;
	
	// Initialise window dimensions
	this->window.width = 1024;
	this->window.height = 770;
	
	// Initialise fonts
	this->fontTitle = NULL;
	this->fontMenu = NULL;
	this->fontStatus = NULL;
	
	// Initialise font colors
	this->white = {255, 255, 255};
	
	// Initialise the current stage;
	this->stage = MAIN;
	
	
	// Initialise the video and font library
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
	// Load all fonts
	this->fontTitle = TTF_OpenFont("res/font/ca.ttf", 65);
	this->fontMenu = TTF_OpenFont("res/font/vcr-osd-mono.ttf", 30);
	this->fontStatus = TTF_OpenFont("res/font/synchro.ttf", 65);
	
	// Check if all fonts were successfully loaded
	if(this->fontTitle==NULL || this->fontMenu==NULL || this->fontStatus==NULL) {
		printf("Unable to load proper font: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Load all resources
	this->crab = IMG_Load("res/img/crab.png");
	this->octopus = IMG_Load("res/img/octopus.png");
	this->squid = IMG_Load("res/img/squid.png");
	this->spaceship = IMG_Load("res/img/spaceship.png");
	
	
	// Set the application icon and create a window
	SDL_WM_SetIcon(IMG_Load("res/img/icon.png"), NULL);
	this->screen = SDL_SetVideoMode(this->window.width, this->window.height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	// Verify if the video mode is available
	if(this->screen==NULL) {
		fprintf(stderr, "Unable to set the video mode: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Set the window title
	SDL_WM_SetCaption("Space Intruders", NULL);
	
	// Display the Main screen
	this->displayMainScreen();
	
	// Keep the window open and wait for a user input
	this->handleEvents();
}

Window::~Window() {
	// Free all allocated memory
	TTF_CloseFont(this->fontTitle);
	TTF_CloseFont(this->fontMenu);
	TTF_CloseFont(this->fontStatus);
	TTF_Quit();
	
	SDL_FreeSurface(this->txt);
	SDL_FreeSurface(this->crab);
	SDL_FreeSurface(this->octopus);
	SDL_FreeSurface(this->squid);
	SDL_FreeSurface(this->spaceship);
	SDL_Quit();
}


void Window::displayMainScreen() {
	// Set a black background
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
	
	// Display the title
	this->txt = TTF_RenderText_Blended(this->fontTitle, "Space Intruders", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 100;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display points table caption
	this->txt = TTF_RenderText_Blended(this->fontMenu, "*SCORE ADVANCE TABLE*", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 250;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the spaceship points
	this->txt = TTF_RenderText_Blended(this->fontMenu, "= ? MYSTERY", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2)+40;
	this->pos.y += 80;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the octopus points
	this->txt = TTF_RenderText_Blended(this->fontMenu, "= 30 POINTS", this->white);		// TODO: integrate point numbers with game variables
	this->pos.y += 60;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the crab points
	this->txt = TTF_RenderText_Blended(this->fontMenu, "= 20 POINTS", this->white);
	this->pos.y += 60;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the squid points
	this->txt = TTF_RenderText_Blended(this->fontMenu, "= 10 POINTS", this->white);
	this->pos.y += 60;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display points table icons
	this->pos.x -= 65;
	this->pos.y = 330;
	SDL_BlitSurface(this->spaceship, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->octopus, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->crab, NULL, this->screen, &pos);
	
	this->pos.x += 5;
	this->pos.y += 60;
	SDL_BlitSurface(this->squid, NULL, this->screen, &pos);
	
	
	// Display the instructions
	this->txt = TTF_RenderText_Blended(this->fontMenu, "PRESS SPACE TO PLAY", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 700;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

void Window::displayInGameScreen() {
	
}


void Window::startNewGame() {
	// Set the current stage to In Game
	this->stage = INGAME;
	
	// Starts a new game
	this->game.reset();
}

void Window::handleEvents() {
	int run = 1;
	SDL_Event event;
	
	while(run) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				run = 0;
				break;
			case SDL_KEYDOWN:
				// Allow to exit the game at any time
				if(event.key.keysym.sym==SDLK_ESCAPE) {
					run = 0;
					break;
				}
				
				// Behaves differently depending on the current stage
				if(this->stage==MAIN) {
					this->handleMainKeyStroke(event.key.keysym.sym);
				}
				else if(this->stage==INGAME) {
					this->handleInGameKeyStroke(event.key.keysym.sym);
				}
				break;
			default:
				break;
		}
	}
}

void Window::handleMainKeyStroke(int key) {
	switch(key) {
    	case SDLK_SPACE:
			this->startNewGame();
			break;
		default:
			break;
	}
}

void Window::handleInGameKeyStroke(int key) {
	switch(key) {
    	case SDLK_SPACE:
			printf("Fire!\n");
			break;
    	case SDLK_LEFT:
			printf("Go left\n");
			break;
    	case SDLK_RIGHT:
			printf("Go right\n");
			break;
		default:
			break;
	}
}
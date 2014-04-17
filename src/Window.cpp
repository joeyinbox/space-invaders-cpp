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
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	TTF_Init();
	
	// Load all fonts
	this->fontTitle = TTF_OpenFont("res/font/ca.ttf", 65);
	this->fontMenu = TTF_OpenFont("res/font/vcr-osd-mono.ttf", 30);
	this->fontStatus = TTF_OpenFont("res/font/synchro.ttf", 30);
	
	// Check if all fonts were successfully loaded
	if(this->fontTitle==NULL || this->fontMenu==NULL || this->fontStatus==NULL) {
		printf("Unable to load proper font: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	
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
	
	// Initialise the baseline of the game
	this->baseline = {0, static_cast<Sint16>(this->window.height-5), static_cast<Uint16>(this->window.width), 5};
	
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
	this->txt = TTF_RenderText_Blended(this->fontMenu, "= 30 POINTS", this->white);
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
	SDL_BlitSurface(this->game.spaceship, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->game.octopus, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->game.crab, NULL, this->screen, &pos);
	
	this->pos.x += 5;
	this->pos.y += 60;
	SDL_BlitSurface(this->game.squid, NULL, this->screen, &pos);
	
	
	// Display the instructions
	this->txt = TTF_RenderText_Blended(this->fontMenu, "PRESS SPACE TO PLAY", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 700;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

void Window::displayInGameScreen() {
	// Set a black background
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
	
	// Display the status
	// Level
	char txt[20];
	sprintf(txt, "LEVEL: %d", this->game.level);
	this->txt = TTF_RenderText_Blended(this->fontStatus, txt, this->white);
	this->pos.x = 20;
	this->pos.y = 20;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Score
	sprintf(txt, "SCORE: %d", this->game.score);
	this->txt = TTF_RenderText_Blended(this->fontStatus, txt, this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 20;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Life
	sprintf(txt, "LIFE: %d", this->game.life);
	this->txt = TTF_RenderText_Blended(this->fontStatus, txt, this->white);
	this->pos.x = this->window.width-this->txt->w-20;
	this->pos.y = 20;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display attackers
	for(int i=0; i<this->game.attacker.size(); i++) {
		this->pos.x = this->game.attackerPosition.x+this->game.attacker[i].x*80+this->game.attacker[i].margin;
		this->pos.y = this->game.attackerPosition.y+this->game.attacker[i].y*80;
		
		switch(this->game.attacker[i].type) {
			case CRAB:
				SDL_BlitSurface(this->game.crab, NULL, this->screen, &pos);
				break;
			case OCTOPUS:
				SDL_BlitSurface(this->game.octopus, NULL, this->screen, &pos);
				break;
			case SQUID:
				SDL_BlitSurface(this->game.squid, NULL, this->screen, &pos);
				break;
			case SPACESHIP:
				SDL_BlitSurface(this->game.spaceship, NULL, this->screen, &pos);
				break;
		}
	}
	
	
	// Draw all bunkers
	for(int i=0; i<this->game.bunker.size(); i++) {
		for(int j=0; j<3; j++) {
			for(int k=0; k<4; k++) {
				if(this->game.bunker[i].part[j][k].state!=DESTROYED) {
					this->pos.y = 600;
					this->pos.x = 170+(i*this->game.bunker[i].width)+(this->game.bunker[i].x*100)+(k*24);
					switch(this->game.bunker[i].part[j][k].type) {
						case TOP_LEFT:
							SDL_BlitSurface(this->game.bunkerTopLeftSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case TOP_RIGHT:
							SDL_BlitSurface(this->game.bunkerTopRightSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case BOTTOM_LEFT:
							this->pos.y += 48;
							SDL_BlitSurface(this->game.bunkerBottomLeftSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case BOTTOM_RIGHT:
							this->pos.y += 48;
							SDL_BlitSurface(this->game.bunkerBottomRightSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case CENTER_LEFT:
							this->pos.y += 48;
							SDL_BlitSurface(this->game.bunkerCenterLeftSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case CENTER_RIGHT:
							this->pos.y += 48;
							SDL_BlitSurface(this->game.bunkerCenterRightSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
						case PLAIN:
							if(j==1) {
								this->pos.y += 24;
							}
							SDL_BlitSurface(this->game.bunkerPlainSurface[this->game.bunker[i].part[j][k].state], NULL, this->screen, &pos);
							break;
					}
				}
			}
		}
	}
	
	// Draw the player
	this->pos.x = this->game.playerPosition.x;
	this->pos.y = this->window.height-15-this->game.player->h;
	SDL_BlitSurface(this->game.player, NULL, this->screen, &pos);
	
	// Draw baseline
	SDL_FillRect(this->screen, &this->baseline, SDL_MapRGB(this->screen->format, 62, 255, 63));
	
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

void Window::displayGameOver() {
	
}


void Window::startNewGame() {
	// Set the current stage to In Game
	this->stage = INGAME;
	
	// Starts a new game
	this->game.reset();
	
	this->displayInGameScreen();
}

void Window::handleEvents() {
	int run = 1;
	int currentTimestamp, previousTimestamp = SDL_GetTicks();
	SDL_Event event;
	
	// Allow to hold a key for repeated actions
	SDL_EnableKeyRepeat(10, 10);
	
	while(run) {
		SDL_PollEvent(&event);
		
		// Pause the application for 30ms
		currentTimestamp = SDL_GetTicks();
		if(currentTimestamp-previousTimestamp>30) {
		    previousTimestamp = currentTimestamp;
			
			// Handle an eventual input from the user
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
			
			// Update the attackers position while in game
			if(this->stage==INGAME) {
				this->game.update(currentTimestamp);
				this->displayInGameScreen();
			}
		}
		else {
			SDL_Delay(30-(currentTimestamp-previousTimestamp));
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
			if(this->game.playerPosition.x>=5) {
				this->game.move(-5);
			}
			break;
    	case SDLK_RIGHT:
			if(this->game.playerPosition.x<=this->window.width-this->game.player->w-5) {
				this->game.move(5);
			}
			break;
		default:
			break;
	}
}
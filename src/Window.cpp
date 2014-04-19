#include <stdio.h>
#include "Window.h"

using namespace std;


/**
 * Initialise all window variables, load fonts and create a window
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
	
	// Initialise the player position
	this->game.setPlayerY(this->window.height-15-this->game.playerSurface->h);
	
	// Display the Main screen
	this->displayMainScreen();
	
	// Keep the window open and wait for a user input
	this->handleEvents();
}

/**
 * Free all allocated memory
 */
Window::~Window() {
	// Free font memory
	TTF_CloseFont(this->fontTitle);
	TTF_CloseFont(this->fontMenu);
	TTF_CloseFont(this->fontStatus);
	TTF_Quit();
	
	// Free surface memory
	SDL_FreeSurface(this->txt);
	SDL_FreeSurface(this->screen);
	SDL_Quit();
}

/**
 * Display the main screen elements
 */
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
	SDL_BlitSurface(this->game.spaceshipSurface, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->game.octopus, NULL, this->screen, &pos);
	
	this->pos.y += 60;
	SDL_BlitSurface(this->game.crab, NULL, this->screen, &pos);
	
	this->pos.x += 5;
	this->pos.y += 60;
	SDL_BlitSurface(this->game.squid, NULL, this->screen, &pos);
	
	
	// Display the instructions
	this->txt = TTF_RenderText_Blended(this->fontMenu, "PRESS ENTER TO PLAY", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 700;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

/**
 * Display in game elements such as the statistics, attackers, the player or the baseline
 */
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
	sprintf(txt, "LIFE: %d", this->game.getPlayerLife());
	this->txt = TTF_RenderText_Blended(this->fontStatus, txt, this->white);
	this->pos.x = this->window.width-this->txt->w-20;
	this->pos.y = 20;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display attackers
	for(int i=0; i<this->game.attacker.size(); i++) {
		this->pos.x = this->game.attackerPosition.x+this->game.attacker[i].x;
		this->pos.y = this->game.attackerPosition.y+this->game.attacker[i].y;
		
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
			default:
				break;
		}
	}
	
	// Display an eventual spaceship
	if(this->game.spaceship.active) {
		this->pos.x = this->game.spaceship.x;
		this->pos.y = this->game.spaceship.y;
		SDL_BlitSurface(this->game.spaceshipSurface, NULL, this->screen, &pos);
	}
	
	
	// Draw all bunkers
	for(int i=0; i<this->game.bunker.size(); i++) {
		for(int j=0; j<this->game.bunker[i].part.size(); j++) {
			this->pos.y = this->game.bunker[i].part[j].y;
			this->pos.x = this->game.bunker[i].part[j].x;
			
			switch(this->game.bunker[i].part[j].type) {
				case TOP_LEFT:
					SDL_BlitSurface(this->game.bunkerTopLeftSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case TOP_RIGHT:
					SDL_BlitSurface(this->game.bunkerTopRightSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case BOTTOM_LEFT:
					SDL_BlitSurface(this->game.bunkerBottomLeftSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case BOTTOM_RIGHT:
					SDL_BlitSurface(this->game.bunkerBottomRightSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case CENTER_LEFT:
					SDL_BlitSurface(this->game.bunkerCenterLeftSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case CENTER_RIGHT:
					SDL_BlitSurface(this->game.bunkerCenterRightSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
				case PLAIN:
					SDL_BlitSurface(this->game.bunkerPlainSurface[this->game.bunker[i].part[j].state], NULL, this->screen, &pos);
					break;
			}
		}
	}
	
	// Draw the bullets
	for(int i=0; i<this->game.bullet.size(); i++) {
		this->pos.x = this->game.bullet[i].x;
		this->pos.y = this->game.bullet[i].y;
		SDL_BlitSurface(this->game.bulletSurface, NULL, this->screen, &pos);
	}
	
	// Draw the player
	this->pos.x = this->game.player.position.x;
	this->pos.y = this->game.player.position.y;
	SDL_BlitSurface(this->game.playerSurface, NULL, this->screen, &pos);
	
	// Draw the baseline
	SDL_FillRect(this->screen, &this->baseline, SDL_MapRGB(this->screen->format, 62, 255, 63));
	
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

/**
 * Display the Game Over screen showing the final score
 */
void Window::displayGameOver() {
	// Set a black background
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
	
	// Display the title
	this->txt = TTF_RenderText_Blended(this->fontTitle, "GAME OVER", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 100;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display the final score
	this->txt = TTF_RenderText_Blended(this->fontMenu, "*FINAL SCORE*", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 250;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the score
	char txt[20];
	sprintf(txt, "%d POINTS", this->game.score);
	this->txt = TTF_RenderText_Blended(this->fontMenu, txt, this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y += 80;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Display the level
	sprintf(txt, "LEVEL: %d", this->game.level);
	this->txt = TTF_RenderText_Blended(this->fontMenu, txt, this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y += 60;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	
	// Display the instructions
	this->txt = TTF_RenderText_Blended(this->fontMenu, "PRESS ENTER TO PLAY AGAIN", this->white);
	this->pos.x = (this->window.width/2)-(this->txt->w/2);
	this->pos.y = 700;
	SDL_BlitSurface(this->txt, NULL, this->screen, &pos);
	
	// Refresh the screen to show all elements
	SDL_Flip(this->screen);
}

/**
 * Reset all related variables and start a new game
 */
void Window::startNewGame() {
	// Set the current stage to In Game
	this->stage = INGAME;
	
	// Starts a new game
	this->game.hardReset();
	
	this->displayInGameScreen();
}

/**
 * Handle general keyboard events and fire update queries to refresh the game
 */
void Window::handleEvents() {
	int run = 1;
	int currentTimestamp, previousTimestamp = SDL_GetTicks();
	SDL_Event event;
	
	// Allow to hold a key for repeated actions
	SDL_EnableKeyRepeat(10, 10);
	
	while(run) {
		SDL_PollEvent(&event);
		// Is the game finished?
		if(!this->game.active && this->stage==INGAME) {
			this->stage = MAIN;
			this->displayGameOver();
		}
		
		// The application will refresh itself every 30ms (~33 fps)
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
			
			// Update the game if needed
			if(this->stage==INGAME) {
				this->game.update(currentTimestamp);
				this->displayInGameScreen();
			}
		}
		else {
			// Pause the application for 30ms
			SDL_Delay(30-(currentTimestamp-previousTimestamp));
		}
	}
}

/**
 * Handle all keyboard events related to the main and game over screen
 */
void Window::handleMainKeyStroke(int key) {
	switch(key) {
		case SDLK_RETURN:
    	case SDLK_KP_ENTER:
			this->startNewGame();
			break;
		default:
			break;
	}
}

/**
 * Handle all keyboard events while in game
 */
void Window::handleInGameKeyStroke(int key) {
	switch(key) {
    	case SDLK_SPACE:
			this->game.playerFire();
			break;
    	case SDLK_LEFT:
			// Prevent to exceed the screen limits
			if(this->game.player.position.x>=5) {
				this->game.move(-5);
			}
			break;
    	case SDLK_RIGHT:
			// Prevent to exceed the screen limits
			if(this->game.player.position.x<=this->window.width-this->game.playerSurface->w-5) {
				this->game.move(5);
			}
			break;
		default:
			break;
	}
}
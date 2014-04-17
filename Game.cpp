#include <stdio.h>
#include "Game.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"
#include "Spaceship.h"

using namespace std;


Game::Game() {
	// Load all resources
	this->player = IMG_Load("res/img/player.png");
	this->crab = IMG_Load("res/img/crab.png");
	this->octopus = IMG_Load("res/img/octopus.png");
	this->squid = IMG_Load("res/img/squid.png");
	this->spaceship = IMG_Load("res/img/spaceship.png");
	
	// Load all bunker resources
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-0.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-1.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-2.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-3.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-0.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-1.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-2.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-3.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-0.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-1.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-2.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-3.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-0.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-1.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-2.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-3.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-0.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-1.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-2.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-3.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-0.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-1.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-2.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-3.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-0.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-1.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-2.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-3.png"));
	
	this->active = false;
}


Game::~Game() {
	// Free all resources
	SDL_FreeSurface(this->crab);
	SDL_FreeSurface(this->octopus);
	SDL_FreeSurface(this->squid);
	SDL_FreeSurface(this->spaceship);
	
	for(int i=0; i<this->bunkerTopLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerTopLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerTopRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerTopRightSurface[i]);
	}
	for(int i=0; i<this->bunkerBottomLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerBottomLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerBottomRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerBottomRightSurface[i]);
	}
	for(int i=0; i<this->bunkerCenterLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerCenterLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerCenterRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerCenterRightSurface[i]);
	}
}

void Game::reset() {
	this->level = 1;
	this->score = 0;
	this->life = 3;
	this->active = true;
	this->attackerPosition.x = 80;
	this->attackerPosition.y = 150;
	this->playerPosition.x = 100;
	this->playerPosition.y = 0;
	
	// Clear an eventual previous array of attackers
	this->attacker.clear();
	
	// Populate all new attackers
	// Insert all squids
	for(int i=0; i<11; i++) {
		Squid squid = Squid(i, 0, this);
		this->attacker.push_back(squid);
	}
	
	// Then all crabs
	for(int i=0; i<11; i++) {
		for(int j=1; j<3; j++) {
			Crab crab = Crab(i, j, this);
			this->attacker.push_back(crab);
		}
	}
	
	// And finally, all octopuses
	for(int i=0; i<11; i++) {
		for(int j=3; j<5; j++) {
			Octopus octopus = Octopus(i, j, this);
			this->attacker.push_back(octopus);
		}
	}
	
	// Clear an eventual previous array of bunkers
	this->bunker.clear();
	
	// Populate all new bunkers
	for(int i=0; i<4; i++) {
		Bunker bunker = Bunker(i);
		this->bunker.push_back(bunker);
	}
}

void Game::decreaseLife() {
	if(--this->life==0) {
		// TODO: implement end of game
		this->active = false;
	}
}

void Game::move(int shift) {
	this->playerPosition.x += shift;
}
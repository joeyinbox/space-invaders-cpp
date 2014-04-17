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
	
	this->active = false;
}


Game::~Game() {
	// Free all resources
	SDL_FreeSurface(this->crab);
	SDL_FreeSurface(this->octopus);
	SDL_FreeSurface(this->squid);
	SDL_FreeSurface(this->spaceship);
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
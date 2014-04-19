#include <time.h>
#include <stdlib.h>
#include "Spaceship.h"

Spaceship::Spaceship(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = SPACESHIP;
	this->resistance = 1;
	this->margin = 0;
	this->x = 0;
	this->width = 44;
	this->height = 19;
	this->active = false;
	
	this->reset();
}

void Spaceship::reset() {
	this->direction = 1;
	this->resistance = 1;
	this->y = 100;
	
	// Initialise a random value
	srand(time(NULL));
	this->worth = (1+rand()%5)*50;
	
	this->active = false;
}

void Spaceship::setDirection(int direction) {
	this->direction = direction;
	this->active = true;
	
	if(direction>0) {
		this->x = -this->width;
	}
	else {
		this->x = 1024;
	}
}
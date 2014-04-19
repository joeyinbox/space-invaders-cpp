#include <time.h>
#include <stdlib.h>
#include "Spaceship.h"

Spaceship::Spaceship(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = SPACESHIP;
	this->resistance = 1;
	this->margin = 0;
	this->x += this->margin;
	this->width = 44;
	this->height = 19;
	
	// Initialise a random value
	srand(time(NULL));
	this->worth = (1+rand()%5)*50;
}
#include <time.h>
#include <stdlib.h>
#include "Spaceship.h"

/**
 * Constructor of the Spaceship class inherited from Attacker to initialise all common variables
 *
 * @param	x		the grid horizontal position of the spaceship; also used to get its position
 * @param	y		the grid vertical position of the spaceship; also used to get its position
 */
Spaceship::Spaceship(int x, int y) : Attacker(x, y) {
	this->type = SPACESHIP;
	this->resistance = 1;
	this->margin = 0;
	this->x = 0;
	this->width = 44;
	this->height = 19;
	this->active = false;
	
	// The game will keep one instance of this object that will need to be resetted everytime it spawns
	this->reset();
}

/**
 * Reset all variables to default values and get a new random worth
 */
void Spaceship::reset() {
	this->direction = 1;
	this->resistance = 1;
	this->y = 100;
	
	// Initialise a random value
	srand(time(NULL));
	this->worth = (1+rand()%5)*50;
	
	this->active = false;
}

/**
 * Set the new direction of the spaceship and re-initialise its horizontal position depending of the former
 */
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
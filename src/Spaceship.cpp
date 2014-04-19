#include "Spaceship.h"

Spaceship::Spaceship(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = SPACESHIP;
	this->worth = 100;
	this->resistance = 1;
	this->margin = 0;
	this->x += this->margin;
	this->width = 44;
	this->height = 19;
}
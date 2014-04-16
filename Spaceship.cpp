#include "Spaceship.h"

Spaceship::Spaceship(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = SPACESHIP;
	this->worth = 100;
	this->resistance = 1;
}
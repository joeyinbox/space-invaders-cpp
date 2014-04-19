#include "Octopus.h"

Octopus::Octopus(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = OCTOPUS;
	this->worth = 30;
	this->resistance = 1;
	this->margin = 5;
	this->x += this->margin;
	this->width = 46;
	this->height = 31;
}
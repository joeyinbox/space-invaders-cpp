#include "Crab.h"
#include <stdio.h>

Crab::Crab(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = CRAB;
	this->worth = 20;
	this->resistance = 1;
	this->margin = 5;
	this->x += this->margin;
	this->width = 47;
	this->height = 35;
}
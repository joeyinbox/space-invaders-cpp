#include "Attacker.h"
#include <stdio.h>

Attacker::Attacker(int x, int y, Game *game) {
	this->grid.x = x;
	this->grid.y = y;
	this->x = x*60;
	this->y = y*60;
	this->game = game;
}

bool Attacker::hurt() {
	// This has been hurt. Is it destroyed?
	return (--this->resistance<=0);
}
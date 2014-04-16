#include "Crab.h"

Crab::Crab(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = CRAB;
	this->worth = 20;
	this->resistance = 1;
}
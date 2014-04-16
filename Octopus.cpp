#include "Octopus.h"

Octopus::Octopus(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = OCTOPUS;
	this->worth = 30;
	this->resistance = 1;
}
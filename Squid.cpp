#include "Squid.h"

Squid::Squid(int x, int y, Game *game) : Attacker(x, y, game) {
	this->type = SQUID;
	this->worth = 10;
	this->resistance = 1;
	this->margin = 10;
}
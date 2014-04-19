#include "Squid.h"

/**
 * Constructor of the Squid class inherited from Attacker to initialise all common variables
 *
 * @param	x		the grid horizontal position of the squid; also used to get its position
 * @param	y		the grid vertical position of the squid; also used to get its position
 */
Squid::Squid(int x, int y) : Attacker(x, y) {
	this->type = SQUID;
	this->worth = 10;
	this->resistance = 1;
	this->margin = 10;
	this->x += this->margin;
	this->width = 36;
	this->height = 36;
}
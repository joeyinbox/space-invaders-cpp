#include "Octopus.h"

/**
 * Constructor of the Octopus class inherited from Attacker to initialise all common variables
 *
 * @param	x		the grid horizontal position of the octopus; also used to get its position
 * @param	y		the grid vertical position of the octopus; also used to get its position
 */
Octopus::Octopus(int x, int y) : Attacker(x, y) {
	this->type = OCTOPUS;
	this->worth = 30;
	this->resistance = 1;
	this->margin = 5;
	this->x += this->margin;
	this->width = 46;
	this->height = 31;
}
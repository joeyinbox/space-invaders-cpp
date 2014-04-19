#include "Crab.h"
#include <stdio.h>

/**
 * Constructor of the Crab class inherited from Attacker to initialise all common variables
 *
 * @param	x		the grid horizontal position of the crab; also used to get its position
 * @param	y		the grid vertical position of the crab; also used to get its position
 */
Crab::Crab(int x, int y) : Attacker(x, y) {
	this->type = CRAB;
	this->worth = 20;
	this->resistance = 1;
	this->margin = 5;
	this->x += this->margin;
	this->width = 47;
	this->height = 35;
}
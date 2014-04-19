#include "Attacker.h"
#include <stdio.h>

/**
 * Constructor of the Attacker class to initialise all common variables
 *
 * @param	x		the grid horizontal position of the attacker; also used to get its position
 * @param	y		the grid vertical position of the attacker; also used to get its position
 */
Attacker::Attacker(int x, int y) {
	this->grid.x = x;
	this->grid.y = y;
	this->x = x*60;
	this->y = y*60;
}

/**
 * Decrease the resistance of the attacker and verify if it is destroyed
 *
 * @return		true if the attacker has been destroyed, otherwise false
 */
bool Attacker::hurt() {
	return (--this->resistance<=0);
}
#include "Bullet.h"

/**
 * Constructor of the class Bullet to initialise all variables
 *
 * @param	x				the horizontal position of the bullet
 * @param	y				the vertical position of the bullet
 * @param	fromPlayer		true if the bullet comes from the player, otherwise false
 * @param	direction		either UP or DOWN
 */
Bullet::Bullet(int x, int y, bool fromPlayer, Direction direction) {
	this->x = x;
	this->y = y;
	this->fromPlayer = fromPlayer;
	this->direction = direction;
}

/**
 * Update the position of the bullet by going either upwards or downwards
 */
void Bullet::move() {
	if(this->direction==UP) {
		this->y -= 15;
	}
	else {
		this->y += 15;
	}
}
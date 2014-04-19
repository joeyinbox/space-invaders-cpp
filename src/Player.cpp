#include "Player.h"

/**
 * Constructor of the Player class to initialise all common variables
 */
Player::Player() {
	// The player vertical position will be set later relatively to the size of the window
	this->position.y = 0;
	this->hardReset();
}

/**
 * Reset all variable to be able to start a new game from scratch
 */
void Player::hardReset() {
	this->life = 3;
	this->reset();
}

/**
 * Reset variables to be able to continue an eventual current wave
 */
void Player::reset() {
	this->position.x = 190;
	this->firing = false;
}

/**
 * Make the player move either to the left or the right
 *
 * @param	shift	positive or negative value to shift the player horizontaly
 */
void Player::move(int shift) {
	this->position.x += shift;
}
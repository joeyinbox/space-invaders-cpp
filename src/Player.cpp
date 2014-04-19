#include "Player.h"

Player::Player() {
	this->position.y = 0;
	this->hardReset();
}

void Player::reset() {
	this->position.x = 190;
	this->firing = false;
}

void Player::hardReset() {
	this->life = 3;
	this->reset();
}

void Player::move(int shift) {
	this->position.x += shift;
}
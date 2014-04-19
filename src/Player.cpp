#include "Player.h"

Player::Player() {
	this->position.y = 0;
	this->reset();
}

void Player::reset() {
	this->life = 3;
	this->position.x = 190;
	this->firing = false;
}

void Player::move(int shift) {
	this->position.x += shift;
}

void Player::explode() {
	
}
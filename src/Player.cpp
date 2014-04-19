#include "Player.h"

Player::Player() {
	this->reset();
}

void Player::reset() {
	this->life = 3;
	this->x = 100;
	this->firing = -1;
}

void Player::move(int shift) {
	this->x += shift;
}

void Player::explode() {
	
}
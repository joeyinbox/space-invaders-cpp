#include "Bullet.h"

Bullet::Bullet(int x, int y, Direction direction) {
	this->x = x;
	this->y = y;
	this->direction = direction;
}

void Bullet::move() {
	if(this->direction==UP) {
		this->y -= 15;
	}
	else {
		this->y += 15;
	}
}

void Bullet::explode() {
	
}
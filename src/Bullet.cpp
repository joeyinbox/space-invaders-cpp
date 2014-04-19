#include "Bullet.h"

Bullet::Bullet(int x, int y, Direction direction) {
	this->x = x;
	this->y = y;
	this->direction = direction;
}

void Bullet::move() {
	if(this->direction==UP) {
		this->y -= 5;
	}
	else {
		this->y += 5;
	}
}

void Bullet::explode() {
	
}
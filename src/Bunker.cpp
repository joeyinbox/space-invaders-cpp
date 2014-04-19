#include "Bunker.h"

/**
 * Constructor of the class Bunker to initialise all 12 parts which constitute itself
 *
 * @param	x	the horizontal position of the bunker
 * @param	y	the vertical position of the bunker
 */
Bunker::Bunker(int x, int y) {
	this->width = 96;
	this->x = 170+(x*(this->width+100));
	this->y = y;
	
	
	// Initialise all 12 parts top to bottom and left to right.
	// 7 types can represent all 12 parts (eg. TOP_LEFT, PLAIN, TOP_RIGHT, etc...)
	Part part;
	
	// First row
	part.state = INITIAL;
	part.type = TOP_LEFT;
	part.x = this->x;
	part.y = this->y;
	this->part.push_back(part);
	
	part.type = PLAIN;
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.type = TOP_RIGHT;
	part.x += this->width/4;
	this->part.push_back(part);
	
	// Second row
	part.type = PLAIN;
	part.x = this->x;
	part.y += this->width/4;
	this->part.push_back(part);
	
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.x += this->width/4;
	this->part.push_back(part);
	
	// Third row
	part.type = BOTTOM_LEFT;
	part.x = this->x;
	part.y += this->width/4;
	this->part.push_back(part);
	
	part.type = CENTER_LEFT;
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.type = CENTER_RIGHT;
	part.x += this->width/4;
	this->part.push_back(part);
	
	part.type = BOTTOM_RIGHT;
	part.x += this->width/4;
	this->part.push_back(part);
}

/**
 * Update the state of a part that has been hurt
 *
 * @param	partId	identifier of the part that has been hurt
 */
void Bunker::hurt(int partId) {
	// The following can be done by incrementing the state by one and check if it is then equal to the value of DESTROYED
	// At the only condition that all states are declared in the right order
	switch(this->part[partId].state) {
		case INITIAL:
			this->part[partId].state = MINOR;
			break;
		case MINOR:
			this->part[partId].state = PARTIAL;
			break;
		case PARTIAL:
			this->part[partId].state = MAJOR;
			break;
		case MAJOR:
			// This part is now destroyed
			this->part.erase(this->part.begin()+partId);
			break;
	}
}
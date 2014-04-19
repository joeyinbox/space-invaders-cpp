#include "Bunker.h"

Bunker::Bunker(int x, int y) {
	this->width = 96;
	this->x = 170+(x*(this->width+100));
	this->y = y;
	
	
	// Initialise all parts
	Part part;
	
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

void Bunker::hurt(int partId) {
	// affect the state of the part
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
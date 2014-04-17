#include "Bunker.h"

Bunker::Bunker(int x) {
	this->x = x;
	this->width = 96;
	
	// Initialise all parts
	std::vector<Part> list;
	Part part;
	part.state = INITIAL;
	
	part.type = TOP_LEFT;
	list.push_back(part);
	part.type = PLAIN;
	list.push_back(part);
	list.push_back(part);
	part.type = TOP_RIGHT;
	list.push_back(part);
	this->part.push_back(list);
	
	list.clear();
	part.type = PLAIN;
	list.push_back(part);
	list.push_back(part);
	list.push_back(part);
	list.push_back(part);
	this->part.push_back(list);
	
	list.clear();
	part.type = BOTTOM_LEFT;
	list.push_back(part);
	part.type = CENTER_LEFT;
	list.push_back(part);
	part.type = CENTER_RIGHT;
	list.push_back(part);
	part.type = BOTTOM_RIGHT;
	list.push_back(part);
	this->part.push_back(list);
}
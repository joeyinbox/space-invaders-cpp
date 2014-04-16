#include <stdio.h>
#include "Game.h"

using namespace std;


Game::Game() {
	this->reset();
}

void Game::reset() {
	this->level = 0;
	this->score = 0;
}
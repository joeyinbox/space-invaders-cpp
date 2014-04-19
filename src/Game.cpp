#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Game.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"
#include "Spaceship.h"

using namespace std;


Game::Game() {
	// Load all resources
	this->playerSurface = IMG_Load("res/img/player.png");
	this->crab = IMG_Load("res/img/crab.png");
	this->octopus = IMG_Load("res/img/octopus.png");
	this->squid = IMG_Load("res/img/squid.png");
	this->spaceship = IMG_Load("res/img/spaceship.png");
	this->bulletSurface = IMG_Load("res/img/bullet.png");
	
	// Load all bunker resources
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-0.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-1.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-2.png"));
	this->bunkerTopLeftSurface.push_back(IMG_Load("res/img/bunker/top-left-3.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-0.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-1.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-2.png"));
	this->bunkerTopRightSurface.push_back(IMG_Load("res/img/bunker/top-right-3.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-0.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-1.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-2.png"));
	this->bunkerBottomLeftSurface.push_back(IMG_Load("res/img/bunker/bottom-left-3.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-0.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-1.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-2.png"));
	this->bunkerBottomRightSurface.push_back(IMG_Load("res/img/bunker/bottom-right-3.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-0.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-1.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-2.png"));
	this->bunkerCenterLeftSurface.push_back(IMG_Load("res/img/bunker/center-left-3.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-0.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-1.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-2.png"));
	this->bunkerCenterRightSurface.push_back(IMG_Load("res/img/bunker/center-right-3.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-0.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-1.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-2.png"));
	this->bunkerPlainSurface.push_back(IMG_Load("res/img/bunker/plain-3.png"));
	
	this->active = false;
	
	// Initialise pseudo-randomness
	srand(time(NULL));
	
	// Set the initial position of bunkers
	this->bunkerInitialY = 600;
}


Game::~Game() {
	// Free all resources
	SDL_FreeSurface(this->playerSurface);
	SDL_FreeSurface(this->crab);
	SDL_FreeSurface(this->octopus);
	SDL_FreeSurface(this->squid);
	SDL_FreeSurface(this->spaceship);
	SDL_FreeSurface(this->bulletSurface);
	
	for(int i=0; i<this->bunkerTopLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerTopLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerTopRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerTopRightSurface[i]);
	}
	for(int i=0; i<this->bunkerBottomLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerBottomLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerBottomRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerBottomRightSurface[i]);
	}
	for(int i=0; i<this->bunkerCenterLeftSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerCenterLeftSurface[i]);
	}
	for(int i=0; i<this->bunkerCenterRightSurface.size(); i++) {
		SDL_FreeSurface(this->bunkerCenterRightSurface[i]);
	}
}

void Game::hardReset() {
	this->level = 1;
	this->score = 0;
	this->player.hardReset();
	this->reset();
}

void Game::reset() {
	this->active = true;
	this->attackerPosition.x = 80;
	this->attackerPosition.y = 150;
	this->direction = 1;
	
	// Hold the time of the beginning of the game
	this->timestamp = SDL_GetTicks();
	
	// Clear an eventual previous array of attackers
	this->attacker.clear();
	
	
	// Populate all new attackers
	// Insert all squids
	for(int i=0; i<11; i++) {
		Squid squid = Squid(i, 0, this);
		this->attacker.push_back(squid);
	}
	
	// Then all crabs
	for(int i=0; i<11; i++) {
		for(int j=1; j<3; j++) {
			Crab crab = Crab(i, j, this);
			this->attacker.push_back(crab);
		}
	}
	
	// And finally, all octopuses
	for(int i=0; i<11; i++) {
		for(int j=3; j<5; j++) {
			Octopus octopus = Octopus(i, j, this);
			this->attacker.push_back(octopus);
		}
	}
	
	// Clear an eventual previous array of bunkers
	this->bunker.clear();
	
	// Populate all new bunkers
	for(int i=0; i<4; i++) {
		Bunker bunker = Bunker(i, this->bunkerInitialY);
		this->bunker.push_back(bunker);
	}
	
	// Clear all eventual bullets
	this->bullet.clear();
	
	// Reset the player informations
	this->player.reset();
}

void Game::update(int now) {
	// Get the first and last attacker horizontaly and the lower one
	int extremH = 0;
	int extremV = 0;
	for(int i=1; i<this->attacker.size(); i++) {
		if(this->direction==1 && this->attacker[i].x>this->attacker[extremH].x) {
			extremH = i;
		}
		else if(this->direction==-1 && this->attacker[i].x<this->attacker[extremH].x) {
			extremH = i;
		}
		
		if(this->attacker[i].y>this->attacker[extremH].y) {
			extremV = i;
		}
	}
	
	// Move the attackers
	this->attackerPosition.x += this->direction*(1+(int)round(this->getSpeedFactor(now)));
	
	// Check if attackers needs to turn
	if((this->direction==1 && this->attacker[extremH].x+this->attackerPosition.x+this->attacker[extremH].width>=1024) || (this->direction==-1 && this->attacker[extremH].x+this->attackerPosition.x<=0)) {
		this->direction *= -1;
		this->attackerPosition.y += 10;
		
		// Have the attackers just landed?
		if(this->attacker[extremV].y+this->attacker[extremV].height+this->attackerPosition.y>this->bunkerInitialY+72) {
			// Game over
			this->active = false;
		}
	}
	
	// Update bullets positions
	for(int i=0; i<this->bullet.size(); i++) {
		this->bullet[i].move();
		
		// Check if the bullet got out of the screen
		if(this->bullet[i].y<0-this->bulletSurface->h || this->bullet[i].y>770) {
			// Eventually allow the player to fire again and remove the bullet
			this->wasPlayerBullet(i);
			this->bullet.erase(bullet.begin()+i);
		}
		else {
			// Check if the bullet touched a bunker
			bool still = true;
			for(int j=0; j<this->bunker.size(); j++) {
				for(int k=0; k<this->bunker[j].part.size(); k++) {
					if(this->bullet[i].x>=this->bunker[j].part[k].x && this->bullet[i].x<=this->bunker[j].part[k].x+(this->bunker[j].width/4)
					&& this->bullet[i].y>=this->bunker[j].part[k].y && this->bullet[i].y<=this->bunker[j].part[k].y+(this->bunker[j].width/4)) {
						// Notify the bunker that it is hurt
						this->bunker[j].hurt(k);
						
						// Eventually allow the player to fire again and remove the bullet
						this->wasPlayerBullet(i);
						this->bullet.erase(bullet.begin()+i);
						
						// There is no break for nested loops in C++ --> A flag or a Goto?
						still = false;
						break;
					}
				}
				
				if(!still) {
					break;
				}
			}
			
			// Check if the bullet touched an attacker
			if(still && this->bullet[i].direction==UP) {
				for(int j=this->attacker.size()-1; j>=0; j--) {
					if(this->bullet[i].x>=this->attackerPosition.x+this->attacker[j].x && this->bullet[i].x<=this->attackerPosition.x+this->attacker[j].x+this->attacker[j].width
					&& this->bullet[i].y>=this->attackerPosition.y+this->attacker[j].y && this->bullet[i].y<=this->attackerPosition.y+this->attacker[j].y+this->attacker[j].height) {
						
						// Increase the score
						this->score += this->attacker[j].worth;
						
						// Destroy eventually that attacker
						if(this->attacker[j].hurt()) {
							this->attacker.erase(attacker.begin()+j);
						}
						
						// Eventually allow the player to fire again and remove the bullet
						this->wasPlayerBullet(i);
						this->bullet.erase(bullet.begin()+i);
						
						// Is the game finished?
						if(this->attacker.size()==0) {
							this->level++;
							this->player.life++;
							this->reset();
						}
						break;
					}
				}
			}
			// Check if the bullet touched the player
			else if(still && this->bullet[i].direction==DOWN) {
				if(this->bullet[i].x>=this->player.position.x && this->bullet[i].x<=this->player.position.x+this->playerSurface->w
				&& this->bullet[i].y+this->bulletSurface->h>=this->player.position.y) {
					this->decreaseLife();
					
					// Remove all bullets and allow the player to fire again
					this->player.firing = false;
					this->bullet.clear();
					break;
				}
			}
		}
	}
	
	// Attackers can fire from time to time
	int probability = rand()%910;
	probability += this->getSpeedFactor(now)*10;
	
	if(probability>900) {
		// Take a lowest random attacker between columns
		vector<int> lowest;
		
		for(int i=0; i<this->attacker.size(); i++) {
			bool found = false;
			for(int j=0; j<lowest.size(); j++) {
				if(this->attacker[i].grid.x==this->attacker[lowest[j]].grid.x) {
					if(this->attacker[i].grid.y>this->attacker[lowest[j]].grid.y) {
						lowest[j] = i;
					}
					found = true;
					break;
				}
			}
			
			if(!found) {
				lowest.push_back(i);
			}
		}
		
		// Make a random attacker fire
		int id = rand()%lowest.size();
		Bullet bullet = Bullet(this->attackerPosition.x+this->attacker[lowest[id]].x+(this->attacker[lowest[id]].width/2), this->attacker[lowest[id]].y+this->attackerPosition.y+this->attacker[lowest[id]].height, false, DOWN);
		this->bullet.push_back(bullet);
	}
}

void Game::decreaseLife() {
	if(--this->player.life==0) {
		this->active = false;
	}
}

void Game::move(int shift) {
	this->player.move(shift);
}

int Game::getPlayerLife() {
	return this->player.life;
}

void Game::setPlayerY(int y) {
	this->player.position.y = y;
}

void Game::wasPlayerBullet(int id) {
	if(this->bullet[id].fromPlayer) {
		this->player.firing = false;
	}
}

void Game::playerFire() {
	if(!this->player.firing) {
		Bullet bullet = Bullet(this->player.position.x+(this->playerSurface->w/2), 755-this->playerSurface->h, true, UP);
		this->bullet.push_back(bullet);
		this->player.firing = true;
	}
}

float Game::getSpeedFactor(int now) {
	return (round(((now-this->timestamp)*this->level)/50))/1000;
}
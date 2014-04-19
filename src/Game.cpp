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


/**
 * Constructor of the Game class to load additional resources and initialise variables
 */
Game::Game() {
	// Load all resources
	this->playerSurface = IMG_Load("res/img/player.png");
	this->crab = IMG_Load("res/img/crab.png");
	this->octopus = IMG_Load("res/img/octopus.png");
	this->squid = IMG_Load("res/img/squid.png");
	this->spaceshipSurface = IMG_Load("res/img/spaceship.png");
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
	
	// The game is not currently started
	this->active = false;
	
	// Initialise pseudo-randomness
	srand(time(NULL));
	
	// Set the initial position of bunkers
	this->bunkerInitialY = 600;
}

/**
 * Destructor of the Game class to free all allocated memory
 */
Game::~Game() {
	// Free all resources
	SDL_FreeSurface(this->playerSurface);
	SDL_FreeSurface(this->crab);
	SDL_FreeSurface(this->octopus);
	SDL_FreeSurface(this->squid);
	SDL_FreeSurface(this->spaceshipSurface);
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

/**
 * Reset all variables to be able to start an entirely new game
 */
void Game::hardReset() {
	this->level = 1;
	this->score = 0;
	this->player.hardReset();
	this->reset();
}

/**
 * Reset all variables to continue an eventual current game
 */
void Game::reset() {
	this->active = true;
	this->attackerPosition.x = 80;
	this->attackerPosition.y = 150;
	this->attackerDirection = 1;
	
	// Hold the time of the beginning of the game
	this->timestamp = SDL_GetTicks();
	
	// Clear an eventual previous attackers
	this->attacker.clear();
	
	
	// Populate all new attackers
	// Insert all squids
	for(int i=0; i<11; i++) {
		Squid squid = Squid(i, 0);
		this->attacker.push_back(squid);
	}
	
	// Then all crabs
	for(int i=0; i<11; i++) {
		for(int j=1; j<3; j++) {
			Crab crab = Crab(i, j);
			this->attacker.push_back(crab);
		}
	}
	
	// And finally, all octopuses
	for(int i=0; i<11; i++) {
		for(int j=3; j<5; j++) {
			Octopus octopus = Octopus(i, j);
			this->attacker.push_back(octopus);
		}
	}
	
	// Clear an eventual previous bunkers
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
	
	// Reset an eventual spaceship
	this->spaceship.reset();
}

/**
 * Update all game element attributes
 * This is called every X decided FPS to refresh for example the position of the attackers, bullets, etc..
 * This also detects all colisions between bullets, attackers, bunkers and the ground.
 * Finally, this make randomly spawn a spaceship for extra bonus
 *
 * @param	now		the current timestamp
 */
void Game::update(int now) {
	// Get the first and last attackers horizontaly and the lower one to detect the boundaries of the attackers' wave
	int extremH = 0;
	int extremV = 0;
	for(int i=1; i<this->attacker.size(); i++) {
		if(this->attackerDirection==1 && this->attacker[i].x>this->attacker[extremH].x) {
			extremH = i;
		}
		else if(this->attackerDirection==-1 && this->attacker[i].x<this->attacker[extremH].x) {
			extremH = i;
		}
		
		if(this->attacker[i].y>this->attacker[extremH].y) {
			extremV = i;
		}
	}
	
	// Check if attackers needs to turn as they reach the limits of the screen
	if((this->attackerDirection==1 && this->attacker[extremH].x+this->attackerPosition.x+this->attacker[extremH].width>=1024) || (this->attackerDirection==-1 && this->attacker[extremH].x+this->attackerPosition.x<=0)) {
		this->attackerDirection *= -1;
		
		// In addition, all attackers move down
		this->attackerPosition.y += 10;
		
		// Have the attackers just landed?
		if(this->attacker[extremV].y+this->attacker[extremV].height+this->attackerPosition.y>this->bunkerInitialY+72) {
			// Game over
			this->active = false;
		}
	}
	
	// Move the attackers
	this->attackerPosition.x += this->attackerDirection*(1+(int)round(this->getSpeedFactor(now)));
	
	// Move an eventual spaceship
	if(this->spaceship.active) {
		this->spaceship.x += this->spaceship.direction*(3+(int)round(this->getSpeedFactor(now)));
		
		// Did it get out of the screen?
		if(this->spaceship.x+this->spaceshipSurface->w<0 || this->spaceship.x>=1024) {
			this->spaceship.reset();
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
			
			// Check if the bullet touched an attacker or a spaceship
			if(still && this->bullet[i].direction==UP) {
				for(int j=this->attacker.size()-1; j>=0; j--) {
					// Attacker
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
						
						// Is the wave finished?
						if(this->attacker.size()==0) {
							this->level++;
							this->player.life++;
							this->reset();
						}
						break;
					}
					// Spaceship
					else if(this->spaceship.active && this->bullet[i].x>=this->spaceship.x && this->bullet[i].x<=this->spaceship.x+this->spaceshipSurface->w 
					&& this->bullet[i].y>=this->spaceship.y && this->bullet[i].y<=this->spaceship.y+this->spaceshipSurface->h) {
						// Increase the score
						this->score += this->spaceship.worth;
						
						// Destroy eventually that spaceship
						if(this->spaceship.hurt()) {
							this->spaceship.reset();
						}
						
						// Eventually allow the player to fire again and remove the bullet
						this->wasPlayerBullet(i);
						this->bullet.erase(bullet.begin()+i);
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
	
	// Attackers can fire from time to time with an increasing chance as the game lasts and the level increases
	int probability = rand()%910;
	probability += this->getSpeedFactor(now)*10;
	
	if(probability>900) {
		// Take a lowest random attacker between all represented columns
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
	
	
	// Finally, a spaceship can spawn
	probability = rand()%1000;
	if(!this->spaceship.active && probability>995) {
		if(probability%2==0) {
			this->spaceship.setDirection(1);
		}
		else {
			this->spaceship.setDirection(-1);
		}
	}
}

/**
 * Decrease the life of the player and therefore, check if the game is over
 */
void Game::decreaseLife() {
	if(--this->player.life==0) {
		this->active = false;
	}
}

/**
 * Make the player move either to the left or the right
 *
 * @param	shift	positive or negative value to shift the player horizontaly
 */
void Game::move(int shift) {
	this->player.move(shift);
}

/**
 * Return the number of remaining lives of the player
 *
 * @return	the number of remaining lives of the player
 */
int Game::getPlayerLife() {
	return this->player.life;
}

/**
 * Set the vertical position of the player
 * Normally called by the Window class to make it relative to the bottom of the latter
 *
 * @param	y	the vertical position of the player
 */
void Game::setPlayerY(int y) {
	this->player.position.y = y;
}

/**
 * Verify if a bullet is emitted by the player to allow the latter to fire again as the bullet will be destroyed
 *
 * @param	id		the identifier of the bullet to verify
 */
void Game::wasPlayerBullet(int id) {
	if(this->bullet[id].fromPlayer) {
		this->player.firing = false;
	}
}

/**
 * Verify if the player can fire a bullet and eventually fire it
 */
void Game::playerFire() {
	if(!this->player.firing) {
		Bullet bullet = Bullet(this->player.position.x+(this->playerSurface->w/2), 755-this->playerSurface->h, true, UP);
		this->bullet.push_back(bullet);
		
		// The player won't be able to fire again as long as its bullet is not destroyed or lost
		this->player.firing = true;
	}
}

/**
 * Return the speed factor calculated with the time elasped since the begining of the wave and the current level
 * Increased by 1 every 50 seconds at level 1
 * Increased by 1 every 25 seconds at level 2
 * And so on..
 *
 * @return	the speed factor
 */
float Game::getSpeedFactor(int now) {
	return (round(((now-this->timestamp)*this->level)/50))/1000;
}
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Attacker.h"
#include "Player.h"
#include "Bunker.h"

#ifndef DEF_GAME
#define DEF_GAME

	struct Position {
		int x;
		int y;
	};

	class Game {
		public:
			int score;
			int level;
			bool active;
			SDL_Surface *playerSurface, *crab, *octopus, *squid, *spaceship, *bulletSurface;
			std::vector<SDL_Surface*> bunkerTopLeftSurface, 
									  bunkerTopRightSurface, 
									  bunkerBottomLeftSurface, 
									  bunkerBottomRightSurface, 
									  bunkerCenterLeftSurface, 
									  bunkerCenterRightSurface,
									  bunkerPlainSurface;
			std::vector<Attacker> attacker;
			std::vector<Bunker> bunker;
			std::vector<Bullet> bullet;
			Position attackerPosition;
			Player player;
			int direction;
			int timestamp, timestampShift;
			
			Game();
			~Game();
			void reset();
			void hardReset();
			void updateScore();
			void updateLevel();
			void decreaseLife();
			void move(int shift);
			int getSpeedFactor(int now);
			void update(int now);
			int getPlayerLife();
			int getPlayerPosition();
			void playerFire();
			void wasPlayerBullet(int id);
	};
	
#endif
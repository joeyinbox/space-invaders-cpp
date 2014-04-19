#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Attacker.h"
#include "Spaceship.h"
#include "Player.h"
#include "Bunker.h"

#ifndef DEF_POSITION
#define DEF_POSITION

	struct Position {
		int x;
		int y;
	};
	
#endif

#ifndef DEF_GAME
#define DEF_GAME

	class Game {
		public:
			int score;
			int level;
			bool active;
			SDL_Surface *playerSurface, *crab, *octopus, *squid, *spaceshipSurface, *bulletSurface;
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
			Spaceship spaceship = Spaceship(0, 2, this);
			int direction;
			int timestamp;
			int bunkerInitialY;
			bool over;
			
			Game();
			~Game();
			void reset();
			void hardReset();
			void updateScore();
			void updateLevel();
			void decreaseLife();
			void move(int shift);
			float getSpeedFactor(int now);
			void update(int now);
			int getPlayerLife();
			void setPlayerY(int y);
			void playerFire();
			void wasPlayerBullet(int id);
	};
	
#endif
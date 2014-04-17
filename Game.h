#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Attacker.h"
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
			int life;
			bool active;
			SDL_Surface *player, *crab, *octopus, *squid, *spaceship;
			std::vector<SDL_Surface*> bunkerTopLeftSurface, 
									  bunkerTopRightSurface, 
									  bunkerBottomLeftSurface, 
									  bunkerBottomRightSurface, 
									  bunkerCenterLeftSurface, 
									  bunkerCenterRightSurface,
									  bunkerPlainSurface;
			std::vector<Attacker> attacker;
			std::vector<Bunker> bunker;
			Position attackerPosition, playerPosition;
			int direction;
			int timestamp, timestampShift;
			
			Game();
			~Game();
			void reset();
			void updateScore();
			void updateLevel();
			void decreaseLife();
			void move(int shift);
			void tick();
			int getSpeedFactor(int now);
			void update(int now);
	};
	
#endif
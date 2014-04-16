#include "Bullet.h"

#ifndef DEF_ATTACKER
#define DEF_ATTACKER
	
	class Game;
	enum Type {CRAB, OCTOPUS, SQUID, SPACESHIP};

	class Attacker {
		public:
			int x;
			int y;
			int worth;
			int resistance;
			int width;
			Type type;
			Game *game;
			
			Attacker(int x, int y, Game *game);
			void moveLeft();
			void moveRight();
			void moveDown();
			void fire();
			void explode();
	};
	
#endif
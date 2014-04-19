#include "Bullet.h"

#ifndef DEF_POSITION
#define DEF_POSITION

	struct Position {
		int x;
		int y;
	};
	
#endif

#ifndef DEF_ATTACKER
#define DEF_ATTACKER
	
	class Game;
	enum Type {CRAB, OCTOPUS, SQUID, SPACESHIP};

	class Attacker {
		public:
			int x;
			int y;
			Position grid;
			int worth;
			int resistance;
			int height;
			int width;
			int margin;
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
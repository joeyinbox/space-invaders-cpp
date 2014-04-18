#include "Attacker.h"

#ifndef DEF_PLAYER
#define DEF_PLAYER

	class Player {
		public:
			int life;
			int x;
			int width;
			bool firing;
			
			Player();
			void move(int direction);
			void explode();
			void reset();
	};
	
#endif
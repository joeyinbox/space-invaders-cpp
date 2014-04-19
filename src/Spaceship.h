#include "Attacker.h"

#ifndef DEF_SPACESHIP
#define DEF_SPACESHIP

	class Spaceship : public Attacker {
		public:
			bool active;
			int direction;
			
			Spaceship(int x, int y, Game *game);
			void reset();
			void setDirection(int direction);
	};
	
#endif
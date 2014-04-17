#include "Attacker.h"

#ifndef DEF_SPACESHIP
#define DEF_SPACESHIP

	class Spaceship : public Attacker {
		public:
			Spaceship(int x, int y, Game *game);
	};
	
#endif
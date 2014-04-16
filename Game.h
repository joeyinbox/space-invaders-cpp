#include <vector>
#include "Attacker.h"

#ifndef DEF_GAME
#define DEF_GAME

	class Game {
		public:
			int score;
			int level;
			std::vector<Attacker> attacker;
			
			Game();
			void reset();
			void updateScore();
			void updateLevel();
			void tick();
			int getSpeedFactor();
	};
	
#endif
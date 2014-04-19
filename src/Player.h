#include "Attacker.h"

#ifndef DEF_POSITION
#define DEF_POSITION

	struct Position {
		int x;
		int y;
	};
	
#endif

#ifndef DEF_PLAYER
#define DEF_PLAYER

	class Player {
		public:
			int life;
			Position position;
			int width;
			bool firing;
			
			Player();
			void move(int direction);
			void reset();
			void hardReset();
	};
	
#endif
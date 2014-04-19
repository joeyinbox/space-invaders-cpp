#ifndef DEF_BULLET
#define DEF_BULLET

	enum Direction {UP, DOWN};

	class Bullet {
		public:
			int x;
			int y;
			bool fromPlayer;
			Direction direction;
			
			Bullet(int x, int y, bool fromPlayer, Direction direction);
			void move();
	};
	
#endif
#ifndef DEF_BULLET
#define DEF_BULLET

	enum Direction {UP, DOWN};

	class Bullet {
		public:
			int x;
			int y;
			Direction direction;
			
			Bullet(int x, int y, Direction direction);
			void move();
			void explode();
	};
	
#endif
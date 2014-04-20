#include <vector>

#ifndef DEF_BUNKER
#define DEF_BUNKER

	enum State {INITIAL, MINOR, PARTIAL, MAJOR};
	enum PartType {TOP_LEFT, TOP_RIGHT, CENTER_LEFT, CENTER_RIGHT, PLAIN};
	struct Part {
		State state;
		PartType type;
		int x;
		int y;
	};

	class Bunker {
		public:
			int x;
			int y;
			int width;
			std::vector<Part> part;
			
			Bunker(int x, int y);
			void hurt(int partId);
	};
	
#endif
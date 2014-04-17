#include <vector>

#ifndef DEF_BUNKER
#define DEF_BUNKER

	enum State {INITIAL, MINOR, PARTIAL, MAJOR, DESTROYED};
	enum PartType {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER_LEFT, CENTER_RIGHT, PLAIN};
	struct Part {
		State state;
		PartType type;
	};

	class Bunker {
		public:
			int x;
			int width;
			std::vector<std::vector<Part> > part;
			
			Bunker(int x);
	};
	
#endif
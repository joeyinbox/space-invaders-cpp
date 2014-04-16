Space-Invaders-cpp
==================

C++ implementation of the Space Invaders game for a school assignment

Requirements
-------------
- SDL framework + SDL_TTF + SDL_Image
- C++11 (the source can be changed easily to be C++9X compliant)

How to Compile on OSX
-------------
```
g++ Window.cpp main.cpp -o SpaceInvaders -std=c++11 -lSDLmain -lSDL -lSDL_Image -lSDL_Ttf -framework Cocoa
```

Credits
-------------
- "Space Invaders" mentions, gameplay and graphics are trademarks of Taito Corporation.
- "Cosmic Alien" TrueType Font Copyright (c) 2001 by ck! [Freaky Fonts]. All rights reserved.
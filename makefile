default: main.cpp sdlinterface.h sdlinterface.cpp block.h block.cpp
	g++ main.cpp sdlinterface.cpp block.cpp -o microblockgen.out -I. -lSDL -lSDL_image

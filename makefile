default: main.cpp headers/sdlinterface.h sdlinterface.cpp headers/block.h block.cpp
	g++ main.cpp sdlinterface.cpp block.cpp -o microblockgen.out -Iheaders -lSDL -lSDL_image -lSDL_ttf

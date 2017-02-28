default: main.cpp sdlinterface.h sdlinterface.cpp
	g++ main.cpp sdlinterface.cpp -o output.out -I. -lSDL -lSDL_image

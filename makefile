CC=$(CROSS)gcc
CXX=$(CROSS)g++
LD=$(CROSS)ld
AR=$(CROSS)ar
PKG_CONFIG=$(CROSS)pkg-config

CXXFLAGS=-std=c++11 -mwindows 
LIBS=-lSDL -lSDL_image -lSDL_ttf
INCLUDES=-I/home/neothefox/src/mxe/usr/i686-w64-mingw32.shared/include/ -Iheaders


default: main.cpp headers/sdlinterface.h sdlinterface.cpp headers/block.h block.cpp
	$(CXX) main.cpp sdlinterface.cpp block.cpp -o microblockgen.out $(INCLUDES) $(LIBS) $(CXXFLAGS)  
debug: main.cpp headers/sdlinterface.h sdlinterface.cpp headers/block.h block.cpp
	g++ main.cpp sdlinterface.cpp block.cpp -g -o microblockgen.out -Iheaders -lSDL -lSDL_image -lSDL_ttf

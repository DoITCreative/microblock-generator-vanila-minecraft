CROSS=
CC=$(CROSS)gcc
CXX=$(CROSS)g++
LD=$(CROSS)ld
AR=$(CROSS)ar
PKG_CONFIG=$(CROSS)pkg-config

CXXFLAGS=-std=c++11
LIBS=-lSDL -lSDL_image -lSDL_ttf
INCLUDES=-Iheaders
CPPFILES=main.cpp sdlinterface.cpp block.cpp
HEADERS=headers/sdlinterface.h headers/block.h 
OUTNAME=microblockgen.out

default: $(CPPFILES) $(HEADERS)	
	$(CXX) $(CPPFILES) -o $(OUTNAME) $(INCLUDES) $(LIBS) $(CXXFLAGS)  
debug: $(CPPFILES) $(HEADERS)	
	$(CXX) $(CPPFILES) -g -o $(OUTNAME) $(INCLUDES) $(LIBS) $(CXXFLAGS)  

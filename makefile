default: main.cpp consoleinterface.h consoleinterface.cpp
	g++ main.cpp consoleinterface.cpp -o output.out -I. -lncurses

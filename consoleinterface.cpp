#include "consoleinterface.h"
#include <iostream>
#include <string>
#include <ncurses.h>

Consoleinterface::Consoleinterface()
{
	finished=0;
	intSizeX=46;
	intSizeY=20;
	selectedBlockName = "";
	selectedLayer = 1;
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	while (!finished) 
	{
		Redraw();
		Controls();
	}

	endwin();
}


void Consoleinterface::Redraw()
{
	clear();
	DrawTitle();
	DrawGrid();
	DrawCursor();
	PrevOut();
}

void Consoleinterface::DrawTitle()
{
	printw("##############################################\n");
	printw("# Selected block: %s         Selected layer: %i #\n",selectedBlockName,selectedLayer);
	refresh();
}

void Consoleinterface::DrawGrid()
{
	for (int y=1; y<=intSizeY; y++) 
	{
		for (int x=1; x<=intSizeX; x++) 
		{
			if (x==curPosX&&y==curPosY)
			{
				printw("X");
			}
			else if (x==1||x==intSizeX||y==1||y==intSizeY) 
			{
				printw("#");
			} 
			else if (x>3&&x<25&&y>4&&y<17) 
			{
				printw(".");
			}
			else 
			{
				printw(" ");
			}
		}
		printw("\n");
	}
	refresh();
}
void Consoleinterface::PrevOut()
{
	if (pOut != "")
	{
		printw("Prev out: %s\n",pOut);
		refresh();
	}
}

void Consoleinterface::DrawCursor()
{
}

void Consoleinterface::Controls()
{
	char command;

	printw("Enter command, h - help, q - quit: ");
	refresh();
	command=getch();
	switch (command) 
	{
	case 'h':
		pOut="help";
		break;
	case 'q':
		pOut="quit";
		finished=1;
		break;
	case 'w':
		pOut="w";
		curPosY--;
		break;
	case 'a':
		pOut="a";
		curPosX--;
		break;
	case 's':
		pOut="s";
		curPosY++;
		break;
	case 'd':
		pOut="d";
		curPosX++;
		break;
	default:
		pOut="Deffault";
	break;
	}
}

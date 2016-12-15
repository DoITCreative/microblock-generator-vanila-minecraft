#include "consoleinterface.h"
#include <iostream>
#include <string>
#include <curses.h>

Consoleinterface::Consoleinterface()
{
	finished=0;
	intSizeX=46;
	intSizeY=20;
	selectedBlockName = "";
	selectedLayer = 1;
	while (!finished) 
	{
		Redraw();
		Controls();
	}
}


void Consoleinterface::Redraw()
{
	ClearScreen();
	DrawTitle();
	DrawGrid();
	DrawCursor();
	PrevOut();
}
void Consoleinterface::ClearScreen()
{
	for (int i=0; i<=50; i++)
	{
		std::cout<<std::endl;
	}
}

void Consoleinterface::DrawTitle()
{
	std::cout << "##############################################" << std::endl;
	std::cout << "# Selected block: " <<selectedBlockName<<"         Selected layer: "
		<< selectedLayer<<" #"<<std::endl;
}

void Consoleinterface::DrawGrid()
{
	for (int y=1; y<=intSizeY; y++) 
	{
		for (int x=1; x<=intSizeX; x++) 
		{
			if (x==curPosX&&y==curPosY)
			{
				std::cout<<"X";
			}
			else if (x==1||x==intSizeX||y==1||y==intSizeY) 
			{
				std::cout<<"#";
			} 
			else if (x>3&&x<25&&y>4&&y<17) 
			{
				std::cout<<".";
			}
			else 
			{
				std::cout<<" ";
			}
		}
		std::cout<<std::endl;
	}
}
void Consoleinterface::PrevOut()
{
	if (pOut != "")
	{
		std::cout<<"Prev out: "<<pOut<<std::endl;
	}
}

void Consoleinterface::DrawCursor()
{
}

void Consoleinterface::Controls()
{
	char command;
	std::cout<<"Testing curses begin"<<std::endl;
	

	std::cout<<key<<std::endl;

	

	std::cout<<"Testing curses end"<<std::endl;

	std::cout<<"Enter command, h - help, q - quit: ";
	std::cin>>command;
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

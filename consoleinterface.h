#include <string>

#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H
class Consoleinterface
{
	public:
		Consoleinterface();
	protected:
		int intSizeX = 0;
		int intSizeY = 0;
		int curPosX = 5;
		int curPosY = 5;
		std::string selectedBlockName = "";
		int selectedLayer = 1;
		bool finished = 0;
		std::string pOut = "";
	private:
		void DrawTitle();
		void DrawGrid();
		void DrawCursor();
		void Controls();
		void Redraw();
		void PrevOut();
};
#endif

#include <iostream>
#include <string>
#include <fstream>
#include "consoleinterface.h"

using namespace std;

//------ Functions declaration start ---------------
string readfile(string filename);
void writefile(string filename, string text);
//------ Functions declaration end ---------------

int main(int argc, char* argv[])
{
	
	Consoleinterface *console = new Consoleinterface();
	return 0;
}


// Reads data from file to string
string readfile(string filename) 
{
	string line;
	string output = "";
	ifstream myfile;
	myfile.open(filename);
	if (myfile.is_open()) {
		cout << "file " << filename << " opened!" <<endl;
		cout << endl;
		while (getline(myfile,line)) {
			output=output+line+"\n";
		}
		myfile.close();
	} else {
		cout << "File can not be readed!" << endl;
	}
	return output;
}
// Writes text to file
void writefile(string filename, string text)
{
	ofstream myfile;
	myfile.open(filename);
	if (myfile.is_open()) {
		myfile << text<< endl;
	} else {
		cout << "Can not open file!" << endl;
	}
}

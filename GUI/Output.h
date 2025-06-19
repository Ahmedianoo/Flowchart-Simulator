#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:

	window* pWind;	//Pointer to the Graphics Window


public:

	Output();

	window* CreateWind(int, int, int, int);

	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	//TODO: Complete the following 2 functions

	void CreateDesignToolBar();	//Tool bar of the design mode

	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar

	void ClearDrawArea();	//Clears the drawing area

	void ClearOutputBar(); //Clears the Output bar

	void PrintMessage(string msg);	//Prints a message on Status bar

	void DrawString(const int, const int, const string);  //Writes a string in the specified location

	// -- Statements Drawing Functions

	void DrawAssign(Point Left, int width, int height, string Text, bool Selected = false);

	void DrawCondtionalStat(Point Upper, int width, int height, string Text, bool Selected = false);

	void DrawReadstat(Point Left, int width, int height, string Text, bool Selected = false);

	void DrawWritestat(Point Left, int width, int height, string Text, bool Selected = false);

	void DrawStart(Point Left, int width, int height, string text, bool Selected = false);

	void DrawEnd(Point Left, int width, int height, string text, bool Selected = false);

	void DrawConnector(Point start, Point end, int checker = 0, bool Selected = false);

	void Output::ClearToolBar();

	void DrawRunString(const int, const int, const string);

	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them

	//TODO: Add DrawConnector function

	~Output();

};

#endif
#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1435;
	UI.height = 740;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 75;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	UI.COND_WDTH = 175;
	UI.COND_HI = 80;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(RED, 3);
	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{

	UI.AppMode = DESIGN;	//Design Mode


	//fill the tool bar 

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem

	ClearToolBar();

	string MenuItemImages[DSN_ITM_CNT];

	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign_Value.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\Assign_Var.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\Assign_Oper.jpg";
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";
	MenuItemImages[ITM_READ] = "images\\Read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
	MenuItemImages[ITM_START] = "images\\Start.jpg";
	MenuItemImages[ITM_END] = "images\\End.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";
	MenuItemImages[ITM_DSN_SWITCH] = "images\\Switch.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Load.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Save.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";
	MenuItemImages[ITM_SELECT] = "images\\Select.jpg";
	MenuItemImages[ITM_COPY] = "images\\Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\Cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Paste.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Delete.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Edit.jpg";

	//TODO: Prepare images for each menu item and add it to the list


	//Draw menu item one image at a time
	for (int i = 0; i < DSN_ITM_CNT; i++) {
		if (i != DSN_ITM_CNT - 1) {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(RED, 6);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, (i + 1) * UI.MenuItemWidth, 0);
		}
		else {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(RED, 3);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, (i + 1) * UI.MenuItemWidth, 0);
		}
	}
	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function

void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{

	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar
	ClearToolBar();

	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\Run.jpg";
	MenuItemImages[ITM_SIM_SWITCH] = "images\\Switch.jpg";
	MenuItemImages[ITM_SIM_EXIT] = "images\\Exit.jpg";

	for (int i = 0; i < SIM_ITM_CNT; i++) {
		if (i != SIM_ITM_CNT - 1) {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(RED, 6);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, (i + 1) * UI.MenuItemWidth, 0);
		}
		else {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(RED, 3);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, (i + 1) * UI.MenuItemWidth, 0);
		}
	}
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	DrawRunString(1200, 50, "OUTPUT AREA");
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() {
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
// 
//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCondtionalStat(Point Upper, int width, int height, string Text, bool Selected) {

	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawLine(Upper.x, Upper.y, Upper.x + width / 2, Upper.y + height / 2);
	pWind->DrawLine(Upper.x, Upper.y, Upper.x - width / 2, Upper.y + height / 2);
	pWind->DrawLine(Upper.x, Upper.y + height, Upper.x - width / 2, Upper.y + height / 2);
	pWind->DrawLine(Upper.x, Upper.y + height, Upper.x + width / 2, Upper.y + height / 2);
	

	pWind->SetPen(BLACK, 2);
	pWind->DrawString((Upper.x - width / 2) + width / 4, (Upper.y + height / 2) - height / 6, Text);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawReadstat(Point Left, int width, int height, string Text, bool Selected) {
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawLine(Left.x, Left.y, Left.x + width, Left.y);
	pWind->DrawLine(Left.x - width / 3, Left.y + height, Left.x + width - width / 3, Left.y + height);
	pWind->DrawLine(Left.x, Left.y, Left.x - width / 3, Left.y + height);
	pWind->DrawLine(Left.x + width, Left.y, Left.x + width - width / 3, Left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 30, Left.y + height / 4, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawWritestat(Point Left, int width, int height, string Text, bool Selected) {
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawLine(Left.x, Left.y, Left.x + width, Left.y);
	pWind->DrawLine(Left.x - width / 3, Left.y + height, Left.x + width - width / 3, Left.y + height);
	pWind->DrawLine(Left.x, Left.y, Left.x - width / 3, Left.y + height);
	pWind->DrawLine(Left.x + width, Left.y, Left.x + width - width / 3, Left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 30, Left.y + height / 4, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawStart(Point Center, int width, int height, string text, bool Selected) {

	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	

	pWind->DrawEllipse(Center.x - width / 2, Center.y - height / 2, Center.x + width / 2, Center.y + height / 2, FRAME);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString((Center.x - width / 2) + width / 3, (Center.y - height / 2) + height / 4.5, text);

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawEnd(Point Center, int width, int height, string text, bool Selected) {

	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawEllipse(Center.x - width / 2, Center.y - height / 2, Center.x + width / 2, Center.y + height / 2, FRAME);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString((Center.x - width / 2) + width / 3, (Center.y - height / 2) + height / 4.5, text);
}

//TODO: Add DrawConnector function

void Output::DrawConnector(Point start, Point end, int checker, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);
	float slope = 0.0;
	float slopenormal = GetSlopes(start, end, slope);
	switch (checker)
	{
	case 0: //normal start end
		if (start.y <= end.y)
		{
			pWind->DrawLine(start.x, start.y, start.x, start.y + 5);
			pWind->DrawLine(start.x, start.y + 5, end.x, start.y + 5);
			pWind->DrawLine(end.x, start.y + 5, end.x, end.y);
		}
		else {
			if (start.x >= end.x && start.y > end.y)
			{
				pWind->DrawLine(start.x, start.y, start.x, start.y + 5);
				pWind->DrawLine(start.x, start.y + 5, end.x, start.y + 5);
				pWind->DrawLine(end.x, start.y + 5, end.x, end.y + UI.ASSGN_HI + 10);
				pWind->DrawLine(end.x, end.y + UI.ASSGN_HI + 10, end.x + UI.ASSGN_WDTH / 2 + 10, end.y + UI.ASSGN_HI + 10);
				pWind->DrawLine(end.x + UI.ASSGN_WDTH / 2 + 10, end.y + UI.ASSGN_HI + 10, end.x + UI.ASSGN_WDTH / 2 + 10, end.y - 10);
				pWind->DrawLine(end.x + UI.ASSGN_WDTH / 2 + 10, end.y - 10, end.x, end.y - 10);
				pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
			}
			else {
				if (start.x < end.x && start.y > end.y)
				{
					pWind->DrawLine(start.x, start.y, start.x, start.y + 5);
					pWind->DrawLine(start.x, start.y + 5, end.x, start.y + 5);
					pWind->DrawLine(end.x, start.y + 5, end.x, end.y + UI.ASSGN_HI + 10);
					pWind->DrawLine(end.x, end.y + UI.ASSGN_HI + 10, end.x - UI.ASSGN_WDTH / 2 - 10, end.y + UI.ASSGN_HI + 10);
					pWind->DrawLine(end.x - UI.ASSGN_WDTH / 2 - 10, end.y + UI.ASSGN_HI + 10, end.x - UI.ASSGN_WDTH / 2 - 10, end.y - 10);
					pWind->DrawLine(end.x - UI.ASSGN_WDTH / 2 - 10, end.y - 10, end.x, end.y - 10);
					pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
				}
			}
		}
		break;
	case 1: // Conditional start point on right

		if (start.x < end.x && start.y + UI.ASSGN_HI / 2 <= end.y)
		{
			pWind->DrawString(start.x + 5, start.y + 5, "true");
			pWind->DrawLine(start.x, start.y, end.x, start.y);
			pWind->DrawLine(end.x, start.y, end.x, end.y);
		}
		else if (start.x < end.x && start.y + UI.ASSGN_HI / 2 > end.y)
		{
			pWind->DrawString(start.x + 5, start.y - 5, "true");
			pWind->DrawLine(start.x, start.y, start.x + 5, start.y);
			pWind->DrawLine(start.x + 5, start.y, start.x + 5, end.y - 10);
			pWind->DrawLine(start.x + 5, end.y - 10, end.x, end.y - 10);
			pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
		}
		else
		{
			pWind->DrawString(start.x + 5, start.y - 5, "true");
			pWind->DrawLine(start.x, start.y, start.x + 5, start.y);
			pWind->DrawLine(start.x + 5, start.y, start.x + 5, end.y - 10);
			pWind->DrawLine(start.x + 5, end.y - 10, end.x, end.y - 10);
			pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
		}
		break;
	case 2:// Conditional start point on left
		if (start.x > end.x && start.y + UI.ASSGN_HI / 2 <= end.y)
		{
			pWind->DrawString(start.x - 5, start.y + 5, "False");
			pWind->DrawLine(start.x, start.y, end.x, start.y);
			pWind->DrawLine(end.x, start.y, end.x, end.y);
		}
		else if (start.x > end.x && start.y + UI.ASSGN_HI / 2 > end.y)
		{
			pWind->DrawString(start.x - 5, start.y - 5, "False");
			pWind->DrawLine(start.x, start.y, start.x - 5, start.y);
			pWind->DrawLine(start.x - 5, start.y, start.x - 5, end.y - 10);
			pWind->DrawLine(start.x - 5, end.y - 10, end.x, end.y - 10);
			pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
		}
		else
		{
			pWind->DrawString(start.x - 5, start.y - 5, "False");
			pWind->DrawLine(start.x, start.y, start.x - 5, start.y);
			pWind->DrawLine(start.x - 5, start.y, start.x - 5, end.y - 10);
			pWind->DrawLine(start.x - 5, end.y - 10, end.x, end.y - 10);
			pWind->DrawLine(end.x, end.y - 10, end.x, end.y);
		}
		break;
	default:
		break;

	}
	pWind->DrawTriangle(end.x, end.y, end.x + 3, end.y - 5, end.x - 3, end.y - 5);
}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	delete pWind;
}

void Output::DrawRunString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(iX, iY, Text);
}

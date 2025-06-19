#include "AddStart.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>
using namespace std;

AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void AddStart::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Add Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);

	while ((Position.x >= (UI.DrawingAreaWidth - UI.ASSGN_WDTH / 2)) || (Position.y >= (UI.height - UI.ASSGN_HI / 2 - UI.StatusBarHeight)) || (Position.y <= (UI.StatusBarHeight)))
	{
		pOut->PrintMessage("Click inside the drawing area, such that the drawing doesn't get out of drawing area");
		pIn->GetPointClicked(Position);
	}
	pOut->ClearStatusBar();
}

void AddStart::Execute()
{
	ReadActionParameters();
	Point Center;
	Center = Position;

	Start* pAssign = new Start(Center);


	pManager->AddStatement(pAssign);

}
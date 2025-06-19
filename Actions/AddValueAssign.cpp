#include "AddValueAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <sstream>
using namespace std;

AddValueAssign::AddValueAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void AddValueAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	Point dummyp;
	bool conti = false;
	while (conti == false)
	{
		pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

		pIn->GetPointClicked(Position);
		if ((((Position.x) + UI.ASSGN_WDTH / 2) >= 0.75 * UI.width) || (Position.y <= UI.ToolBarHeight) || (Position.y + UI.ASSGN_HI >= UI.height - UI.StatusBarHeight))
		{
			pOut->PrintMessage("you cannot draw in this area,click to continue");
			pIn->GetPointClicked(dummyp);
		}
		else
		{
			conti = true;
		}
	}
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Add the LHS for the statment");
	LHS = pIn->GetVariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Add the RHS for the statment");
	RHS = pIn->GetValue(pOut);
	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddValueAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	ValueAssign* pAssign = new ValueAssign(Corner, LHS, RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list              
}
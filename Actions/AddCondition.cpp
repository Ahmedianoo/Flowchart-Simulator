#include "..\HelperFn.h"
#include "AddCondition.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/Output.h"
#include <sstream>
using namespace std;

AddCondition::AddCondition(ApplicationManager* pAppManager):Action(pAppManager)
{}


void AddCondition::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Conditional Statement: Click to add the statement");



	pIn->GetPointClicked(Position);

	bool isPositionValid = false;


	while (isPositionValid == false) {
		if (Position.x > UI.DrawingAreaWidth || Position.y > UI.height - UI.StatusBarHeight || Position.y < UI.ToolBarHeight
			|| Position.x + UI.COND_WDTH / 2 > UI.DrawingAreaWidth || Position.x - (UI.COND_WDTH / 2) < 0
			|| Position.y + UI.COND_HI > UI.height - UI.StatusBarHeight) {
			pOut->PrintMessage("Enter a valid position for the conditional statement");
			pIn->GetPointClicked(Position);
		}
		else {
			isPositionValid = true;
		}
	
	}

	pOut->ClearStatusBar();
	
	bool flag = 0;
	while (flag == 0) {

		pOut->PrintMessage("Enter the left hand side of the condition");
		do {
			LHS = pIn->GetString(pOut);
			if (ValueOrVariable(LHS) == INVALID_OP) {
				pOut->PrintMessage("Enter a valid left hand side");
			}
		} while (ValueOrVariable(LHS) == INVALID_OP);
		
		pOut->PrintMessage("Enter the comparison operator");
		CompOperator = pIn->GetCompOperator(pOut);
		
		pOut->PrintMessage("Enter the right hand side of the condition");
		do {
			RHS = pIn->GetString(pOut);
			if (ValueOrVariable(RHS) == INVALID_OP) {
				pOut->PrintMessage("Enter a valid right hand side");
			}
		} while (ValueOrVariable(RHS) == INVALID_OP);

		if (IsValue(LHS) == true && IsValue(LHS) == true) {
			Point P;
			pOut->PrintMessage("Enter a valid condition, click to continue");
			pIn->GetPointClicked(P);
		}
		else {
			flag = 1;
		}

	}
	
	pOut->ClearStatusBar();
}


void AddCondition::Execute()
{
	ReadActionParameters();
	
	Condition* pCond = new Condition(Position, LHS, CompOperator, RHS);

	pManager->AddStatement(pCond); 

}

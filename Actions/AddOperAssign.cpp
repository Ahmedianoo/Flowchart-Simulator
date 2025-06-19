#include "..\Actions\AddOperAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Statements\OperAssign.h"
AddOperAssign::AddOperAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddOperAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	bool cond = false;
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
	pOut->PrintMessage("Add the LHS for the statment");
	LHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the Left hand side of the Arithmatic operator");
	do
	{
		LHS_Of_Arithmaticoperator = pIn->GetString(pOut);
		if (ValueOrVariable(LHS_Of_Arithmaticoperator) == INVALID_OP)
		{
			pOut->PrintMessage("what you entered is neither a value no a variable,click to continue");
			pIn->GetPointClicked(dummyp);

		}
		else
		{
			cond = true;
		}
	} while (cond == false);

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the Arithmatic operator");
	Arithmaticoperator = pIn->GetArithOperator(pOut);

	cond = false;
	pOut->PrintMessage("Enter the RHS hand side of the Arithmatic operator");
	do
	{
		RHS_Of_Arithmaticoperator = pIn->GetString(pOut);
		if (ValueOrVariable(RHS_Of_Arithmaticoperator) == INVALID_OP)
		{
			pOut->PrintMessage("what you entered is neither a value no a variable,click to continue");
			pIn->GetPointClicked(dummyp);

		}
		else
		{
			cond = true;
		}
	} while (cond == false);
}

void AddOperAssign::Execute()
{
	ReadActionParameters();
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	OperAssign* pAssign = new OperAssign(Corner, LHS, RHS_Of_Arithmaticoperator, LHS_Of_Arithmaticoperator, Arithmaticoperator);
	pManager->AddStatement(pAssign);
}



/**/
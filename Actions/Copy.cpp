#include "Copy.h"

#include "../ApplicationManager.h"

#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Statements/Condition.h"
#include "../Statements/OperAssign.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
#include "../Statements/ValueAssign.h"
#include "../Statements/VariableAssign.h"

#include <sstream>
using namespace std;

Copy::Copy(ApplicationManager* pAppManager):Action(pAppManager)
{}

void Copy::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	Statement* copy;
	copy = pManager->GetSelectedStatement();
	Statement* test;
    

	if (copy != NULL) {
		while (true) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL) {
				string LHS, CompOperator, RHS;
				LHS = ((Condition*)copy)->getLHS();
				CompOperator = ((Condition*)copy)->getCompOperator();
				RHS = ((Condition*)copy)->getRHS();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new Condition(P, LHS, CompOperator, RHS);
				break;
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL) {
				string RHS, LHS;
				LHS = ((OperAssign*)copy)->getLHS();
				RHS = ((OperAssign*)copy)->getLHSofAO();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new OperAssign(P, LHS, RHS);
				break;
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL) {
				string LHS;
				double RHS;
				LHS = ((ValueAssign*)copy)->getLHS();
				RHS = ((ValueAssign*)copy)->getRHS();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new ValueAssign(P, LHS, RHS);
				break;
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL) {
				string RHS, LHS;
				LHS = ((VariableAssign*)copy)->getLHS();
				RHS = ((VariableAssign*)copy)->getRHS();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new VariableAssign(P, LHS, RHS);
				break;
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL) {
				string variableName;
				double value;
				variableName = ((Read*)copy)->GetVariableName();
				value = ((Read*)copy)->GetValue();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new Read(P, variableName, value);
				break;
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL) {
				string print;
				print = ((Write*)copy)->GetPrint();
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new Write(P, print);
				break;
			}

			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new Start(P);
				break;
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL) {
				Point P;
				P.x = 0;
				P.y = 0;
				CopiedStat = new End(P);
				break;
			}
		}
	}
	else{
		CopiedStat = NULL;
		pOut->PrintMessage("No selected statement to copy, click any where to continue");
		Point P;
		pIn->GetPointClicked(P);
		pOut->ClearStatusBar();
	}

}


void Copy::Execute()
{
	ReadActionParameters();

	if (CopiedStat != NULL) {
		pManager->SetClipboard(CopiedStat);
	}
	
}

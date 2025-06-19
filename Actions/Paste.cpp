#include "Paste.h"

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

Paste::Paste(ApplicationManager* pAppManager):Action(pAppManager)
{}

void Paste::ReadActionParameters() {

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	Statement* copy;
	copy = pManager->GetClipboard();
	Statement* test;


	if (copy != NULL) {
		pOut->PrintMessage("Click at the new location to paste the statement to");
		pIn->GetPointClicked(newPosition);

		while (true) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL) {
				string LHS, CompOperator, RHS;
				LHS = ((Condition*)copy)->getLHS();
				CompOperator = ((Condition*)copy)->getCompOperator();
				RHS = ((Condition*)copy)->getRHS();
				PastedStat = new Condition(newPosition, LHS, CompOperator, RHS);
				break;
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL) {
				string RHS, LHS;
				LHS = ((OperAssign*)copy)->getLHS();
				RHS = ((OperAssign*)copy)->getLHSofAO();
				PastedStat = new OperAssign(newPosition, LHS, RHS);
				break;
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL) {
				string LHS;
				double RHS;
				LHS = ((ValueAssign*)copy)->getLHS();
				RHS = ((ValueAssign*)copy)->getRHS();
				PastedStat = new ValueAssign(newPosition, LHS, RHS);
				break;
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL) {
				string RHS, LHS;
				LHS = ((VariableAssign*)copy)->getLHS();
				RHS = ((VariableAssign*)copy)->getRHS();
				PastedStat = new VariableAssign(newPosition, LHS, RHS);
				break;
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL) {
				string variableName;
				double value;
				variableName = ((Read*)copy)->GetVariableName();
				value = ((Read*)copy)->GetValue();
				PastedStat = new Read(newPosition, variableName, value);
				break;
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL) {
				string print;
				print = ((Write*)copy)->GetPrint();
				PastedStat = new Write(newPosition, print);
				break;
			}

			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				PastedStat = new Start(newPosition);
				break;
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL) {
				PastedStat = new End(newPosition);
				break;
			}
		}
	}
	else {
		PastedStat = NULL;
		pOut->PrintMessage("No selected statement to paste, click any where to continue");
		Point P;
		pIn->GetPointClicked(P);
		pOut->ClearStatusBar();
	}
	

}


void Paste::Execute() {
	ReadActionParameters();

	if (PastedStat != NULL) {
		pManager->AddStatement(PastedStat);
	}
}

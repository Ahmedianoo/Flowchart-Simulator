#include "AddRead.h"
#include "..\GUI/Input.h"
#include"..\GUI/Output.h"
#include"..\ApplicationManager.h"
#include "..\Statements/Read.h"
#include"..\Statements/Statement.h"

AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager) {};

void AddRead::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Read Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	variable = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	Value = 0;
	//Value = pIn->GetValue(pOut);



}
void AddRead::Execute() {
	ReadActionParameters();
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Read* pRead = new Read(Corner, variable, Value);
	pManager->AddStatement(pRead);
};
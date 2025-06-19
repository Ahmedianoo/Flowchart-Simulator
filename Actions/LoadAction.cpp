#include "LoadAction.h"
#include"../ApplicationManager.h"
#include<fstream>
#include"../Statements/Read.h"
#include"../Statements/Write.h"
#include"../Statements/Condition.h"
#include"../Statements/End.h"
#include"../Statements/OperAssign.h"
#include"../Statements/Start.h"
#include"../Statements/ValueAssign.h"
#include"../Statements/VariableAssign.h"

LoadAction::LoadAction(ApplicationManager* pAppManager) :Action(pAppManager) {};

void LoadAction::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (invalid = true) {
		pOut->PrintMessage("Enter A Valid File Name To Load From");
		File_Name = pIn->GetString(pOut);
		File_Name += ".txt";
	}
	else {
		pOut->PrintMessage("Enter File Name To Load From");
		File_Name = pIn->GetString(pOut);
		File_Name += ".txt";
	}
};
void LoadAction::Execute() {
	invalid = false;
	bool valid = false;
	ifstream MyFile;
	while (valid == false) {
		ReadActionParameters();
		MyFile.open(File_Name);
		if (MyFile.is_open()) {
			valid = true;
		}
		else {
			invalid = true;
		}
	}
	pManager->LoadAll(MyFile);
	pManager->UpdateInterface();

};
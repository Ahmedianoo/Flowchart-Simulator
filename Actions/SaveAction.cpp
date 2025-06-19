#include "SaveAction.h"
#include"../ApplicationManager.h"
#include<fstream>
SaveAction::SaveAction(ApplicationManager* pAppManager) :Action(pAppManager) {};


void SaveAction::ReadActionParameters() {
	bool valid = false, second = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	while (valid != true) {
		if (second != true) {
			pOut->PrintMessage("save: write file name");
		}
		else {
			pOut->PrintMessage("Enter a valid file name");
		}
		file_name = pIn->GetString(pOut);
		valid = IsFileName(file_name);
		if (valid != true) {
			second = true;
		}
		else {
			file_name += ".txt";
		}

	}
	pOut->ClearStatusBar();

};




void SaveAction::Execute() {
	ReadActionParameters();
	ofstream MyFile(file_name);
	pManager->SaveAll(MyFile);
	MyFile.close();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Saved!!");
};
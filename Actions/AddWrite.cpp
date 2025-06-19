#include"AddWrite.h"
#include "..\GUI/Input.h"
#include"..\GUI/Output.h"
#include"..\ApplicationManager.h"
#include"..\HelperFn.h"
#include"..\Statements/Write.h"

AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager) {};
void AddWrite::Execute() {
	ReadActionParameters();
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	Write* pWrite = new Write(Corner, print);
	pManager->AddStatement(pWrite);

};
void AddWrite::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Write Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	bool second = 0;
	int checklast = -1, checkfirst = -1;
	bool valid = false;
	string str = "\"";
	while (valid != true) {
		if (second == 0) {
			pOut->PrintMessage("Enter a variable or a string \"text\" ");
		}
		else {
			pOut->PrintMessage("Enter a valid variable or a string 'text' ");
		}
		userinput = pIn->GetString(pOut);
		checklast = userinput.find_last_not_of(str);
		checkfirst = userinput.find_first_not_of(str);
		pOut->ClearStatusBar();
		if (checklast != userinput.length() - 1 && checkfirst != 0) {
			print = userinput;
			valid = true;
		}
		else {
			valid = IsVariable(userinput);
			if (valid == true) {
				print = userinput;
			}
			else {
				second = 1;
			}
		}


	}
};
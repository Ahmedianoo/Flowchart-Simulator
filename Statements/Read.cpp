#include "Read.h"
#include "../GUI/UI_Info.h"
#include <sstream>
#include<fstream>
#include <iostream>
using namespace std;
#include <string.h>


Read::Read(Point corner, string text, double input_value) {
	value = input_value;
	variable_name = text;
	UpdateStatementText();
	Center = corner;
	pOutConn = NULL;

	Inlet.y = Center.y;
	Inlet.x = Center.x + UI.ASSGN_WDTH / 2;

	Outlet.x = Center.x - (UI.ASSGN_WDTH / 3) + UI.ASSGN_WDTH / 2;
	Outlet.y = Center.y + UI.ASSGN_HI;



}
void Read::Draw(Output* pOut)const {
	pOut->DrawReadstat(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
void Read::UpdateStatementText() {
	ostringstream T;
	T << "Read " << variable_name;
	Text = T.str();

}


Point Read::getInlet() {
	return Inlet;
};
Point Read::getOutlet(int x) {
	return Outlet;
};
bool Read::Is_In_Region(Point& p1) {
	if (p1.x >= Center.x - UI.ASSGN_WDTH && p1.x <= Center.x + UI.ASSGN_WDTH && p1.y >= Center.y - UI.ASSGN_HI && p1.y <= Center.y + UI.ASSGN_HI) {
		return true;
	}
	return false;
};
void Read::SetConnector(Connector* pOutConn) {
	this->pOutConn = pOutConn;
};
Connector* Read::GetConnector(int checker) {
	return pOutConn;
};
double Read::GetValue() {
	return value;
}
string Read::GetVariableName() {
	return variable_name;
}

void Read::Save(ofstream& OutFile) {
	OutFile << "READ   " << ID << "  " << Center.x << "  " << Center.y << "   " << variable_name;
};
void Read::Load(ifstream& OutFile) {
	OutFile >> variable_name;
	UpdateStatementText();

};

void Read::SimulateRead(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, Input* pIn,int writecount) {
	

	for (int i = 0; i < variablescount; i++) {
		if (variable_name == allvariables[i]) {
			value = pIn->GetValue(pOut);
			corespondingarray[i] = value;
			return;
		}
	}

	allvariables[variablescount] = variable_name;
	value = pIn->GetValue(pOut);
	corespondingarray[variablescount] = value;
	variablescount++;
	return;

}

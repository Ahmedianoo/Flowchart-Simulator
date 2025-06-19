#include "VariableAssign.h"
#include <sstream>
#include <iostream>
using namespace std;
void VariableAssign::UpdateStatementText()
{
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;
	UpdateStatementText();
	LeftCorner = Lcorner;
	pOutConn = NULL;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VariableAssign::setLHS(const string& L)
{
	LHS = L;
}

void VariableAssign::setRHS(string R)
{
	RHS = R;
}

Point VariableAssign::getInlet()
{
	return Inlet;
}

Point VariableAssign::getOutlet(int x)
{
	return Outlet;
}

void VariableAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

bool VariableAssign::Is_In_Region(Point& p1)
{
	if ((p1.x >= (LeftCorner.x)) && (p1.x <= (LeftCorner.x + UI.ASSGN_WDTH)) && (p1.y >= LeftCorner.y) && (p1.y <= LeftCorner.y + UI.ASSGN_HI))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void VariableAssign::SetConnector(Connector* pOutConn)
{
	if (this->pOutConn != NULL)
	{
		delete this->pOutConn;
	}
	this->pOutConn = pOutConn;
}

Connector* VariableAssign::GetConnector(int checker)
{
	return nullptr;
}

VariableAssign::~VariableAssign()
{
	if (pOutConn != NULL)
	{
		delete pOutConn;
	}
}

string VariableAssign::getLHS() {
	return LHS;
}

string VariableAssign::getRHS() {
	return RHS;
}

void VariableAssign::Save(ofstream& OutFile) {
	OutFile << "VAR_ASSIGN" << " " << ID << "  " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS;
}
void VariableAssign::Load(ifstream& Infile) {
	Infile >> LHS >> RHS;
	UpdateStatementText();

}

void VariableAssign::Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& CountOfVariables, Output* pOut, int writecount)

{
	allvariables[CountOfVariables] = LHS;
	CountOfVariables++;
	bool checkifexist = false;
	for (int i = 0; i < CountOfVariables - 1; i++)
	{
		if (allvariables[i] == LHS)
		{
			//corespondingarray[i] = RHS;
			checkifexist = true;
			break;
		}
	}
	for (int i = 0; i < CountOfVariables; i++)
	{
		if (allvariables[i] == RHS)
			if (checkifexist == true)
			{
				CountOfVariables--;
				allvariables[CountOfVariables] = "";
				corespondingarray[CountOfVariables - 1] = corespondingarray[i];

			}
			else
			{
				corespondingarray[CountOfVariables - 1] = corespondingarray[i];
			}
	}

}
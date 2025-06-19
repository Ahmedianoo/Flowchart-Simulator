#include "ValueAssign.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

Point ValueAssign::getInlet()
{
	return Inlet;
}

Point ValueAssign::getOutlet(int x)
{
	return Outlet;
}

void ValueAssign::SetConnector(Connector* pOutConn)
{
	if (this->pOutConn != NULL)
	{
		delete this->pOutConn;
	}
	this->pOutConn = pOutConn;
}

Connector* ValueAssign::GetConnector(int checker)
{
	return pOutConn;
}

void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}

bool ValueAssign::Is_In_Region(Point& p1)
{
	if ((p1.x >= (LeftCorner.x )) && (p1.x <= (LeftCorner.x + UI.ASSGN_WDTH)) && (p1.y >= LeftCorner.y) && (p1.y <= LeftCorner.y + UI.ASSGN_HI))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

ValueAssign::~ValueAssign()
{
	if (pOutConn != NULL)
	{
		delete pOutConn;
	}
}

string ValueAssign::getLHS() {
	return LHS;
}

double ValueAssign::getRHS() {
	return RHS;
}

void ValueAssign::Save(ofstream& OutFile) {
	OutFile << "VAL_ASSIGN" << " " << ID << "  " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS;
}
void ValueAssign::Load(ifstream& Infile) {
	Infile >> LHS >> RHS;
	UpdateStatementText();

}

void ValueAssign::Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, int writecount)
{
	allvariables[variablescount] = LHS;
	variablescount++;
	bool checkifexist = false;
	for (int i = 0; i < variablescount - 1; i++)
	{
		if (allvariables[i] == LHS)
		{
			//corespondingarray[i] = RHS;
			checkifexist = true;
			break;
		}
	}
	if (checkifexist == true)
	{
		variablescount--;
		allvariables[variablescount] = "";
		corespondingarray[variablescount - 1] = RHS;

	}
	else
	{
		corespondingarray[variablescount - 1] = RHS;
	}
}
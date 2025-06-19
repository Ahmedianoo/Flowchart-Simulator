#include "OperAssign.h"
#include <sstream>
#include <iostream>
using namespace std;

void OperAssign::UpdateStatementText()
{
	ostringstream T;
	//string RHS = LHS_Of_Arithmaticoperator + " " + Arithmaticoperator + " " + RHS_Of_Arithmaticoperator;
	T << LHS << " = " << LHS_Of_Arithmaticoperator << " " + Arithmaticoperator << " " << RHS_Of_Arithmaticoperator;
	Text = T.str();
}

OperAssign::OperAssign(Point Lcorner, string LeftHS ,string RightHSOfAO, string LEFTHSOfAO, string AO )
{
	IsTheRHSValue = false;
	IsTheLHSValue = false;
	LHS = LeftHS;
	RHS_Of_Arithmaticoperator = RightHSOfAO;
	LHS_Of_Arithmaticoperator = LEFTHSOfAO;
	Arithmaticoperator = AO;
	UpdateStatementText();
	LeftCorner = Lcorner;
	pOutConn = NULL;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	if (ValueOrVariable(RHS_Of_Arithmaticoperator) == VALUE_OP)
	{
		RHS_Of_Arithmaticoperator_In_caseOfValue = stod(RHS_Of_Arithmaticoperator);
		IsTheRHSValue = true;
	}
	if (ValueOrVariable(LHS_Of_Arithmaticoperator) == VALUE_OP)
	{
		LHS_Of_Arithmaticoperator_In_caseOfValue = stod(LHS_Of_Arithmaticoperator);
		IsTheRHSValue = true;
	}
}

string OperAssign::getRightHSOfAO()
{
	return RHS_Of_Arithmaticoperator;
	
}

string OperAssign::getLHS()
{
	return LHS;
	
}

string OperAssign::getLHSofAO()
{
	return LHS_Of_Arithmaticoperator;
}

void OperAssign::setLHS(const string& L)
{
	LHS = L;
}

void OperAssign::setRightHSOfAO(string R)
{
	RHS_Of_Arithmaticoperator = R;
	if (ValueOrVariable(RHS_Of_Arithmaticoperator) == VALUE_OP)
	{
		RHS_Of_Arithmaticoperator_In_caseOfValue = stod(RHS_Of_Arithmaticoperator);
		IsTheRHSValue = true;
	}
}

void OperAssign::setAO(string ao)
{
	Arithmaticoperator = ao;
}

void OperAssign::setLEFTHSOfAO(string La)
{
	LHS_Of_Arithmaticoperator = La;
	if (ValueOrVariable(LHS_Of_Arithmaticoperator) == VALUE_OP)
	{
		LHS_Of_Arithmaticoperator_In_caseOfValue = stod(LHS_Of_Arithmaticoperator);
		IsTheRHSValue = true;
	}
}

Point OperAssign::getInlet()
{
	return Inlet;
}

Point OperAssign::getOutlet(int x)
{
	return Outlet;
}

bool OperAssign::Is_In_Region(Point& p1)
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

void OperAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}



void OperAssign::SetConnector(Connector* pOutConn)
{
	if (this->pOutConn != NULL)
	{
		delete this->pOutConn;
	}
	this->pOutConn = pOutConn;
}



Connector* OperAssign::GetConnector(int checker)
{
	return pOutConn;
}

void OperAssign::Save(ofstream& OutFile) {
	OutFile << "OP_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << LHS_Of_Arithmaticoperator << "  ";

	if (Arithmaticoperator == "+") {
		OutFile << "ADD";
	}
	if (Arithmaticoperator == "-") {
		OutFile << "SUB";
	}
	if (Arithmaticoperator == "*") {
		\
			OutFile << "MUL";
	}
	if (Arithmaticoperator == "/") {
		OutFile << "DIV";
	}

	OutFile << "  " << RHS_Of_Arithmaticoperator;
};

void OperAssign::Load(ifstream& OutFile) {
	OutFile >> LHS >> LHS_Of_Arithmaticoperator >> Arithmaticoperator >> RHS_Of_Arithmaticoperator;

	if (Arithmaticoperator == "ADD") {
		Arithmaticoperator = "+";
	};
	if (Arithmaticoperator == "SUB") {
		Arithmaticoperator = "-";
	};
	if (Arithmaticoperator == "MUL") {
		Arithmaticoperator = "*";
	};
	if (Arithmaticoperator == "DIV") {
		Arithmaticoperator = "/";
	};
	UpdateStatementText();


}

void OperAssign::Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& CountOfVariables, Output* pOut, int writecount)

{
	allvariables[CountOfVariables] = LHS;
	CountOfVariables++;
	bool checkifexist = false;
	for (int i = 0; i < CountOfVariables - 1; i++)
	{
		if (allvariables[i] == LHS)
		{
			checkifexist = true;
			break;
		}
	}
	if (checkifexist == true)
	{
		allvariables[CountOfVariables] = "";
		CountOfVariables--;

	}


	int LHSindex, RHSindex;
	bool checkLHS = IsVariable(LHS_Of_Arithmaticoperator);
	if (checkLHS == true)
	{
		for (int i = 0; i < CountOfVariables; i++)
		{
			if (allvariables[i] == LHS_Of_Arithmaticoperator)
			{
				LHSindex = i;
				break;
			}
		}
	}

	bool checkRHS = IsVariable(RHS_Of_Arithmaticoperator);

	if (checkRHS == true)
	{
		for (int i = 0; i < CountOfVariables; i++)
		{
			if (allvariables[i] == RHS_Of_Arithmaticoperator)
			{
				RHSindex = i;
				break;
			}
		}
	}

	if (checkRHS == false && checkLHS == false)
	{
		if (Arithmaticoperator == "+")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue + LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "-")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue - LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "*")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue * LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "/")
		{
			corespondingarray[CountOfVariables - 1] = LHS_Of_Arithmaticoperator_In_caseOfValue / RHS_Of_Arithmaticoperator_In_caseOfValue;
		}
	}
	else if (checkLHS == true && checkRHS == false)
	{
		if (Arithmaticoperator == "+")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue + corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "-")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue - corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "*")
		{
			corespondingarray[CountOfVariables - 1] = RHS_Of_Arithmaticoperator_In_caseOfValue * corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "/")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[LHSindex] / RHS_Of_Arithmaticoperator_In_caseOfValue;
		}
	}
	else if (checkLHS == false && checkRHS == true)
	{
		if (Arithmaticoperator == "+")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] + LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "-")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] - LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "*")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] * LHS_Of_Arithmaticoperator_In_caseOfValue;
		}
		else if (Arithmaticoperator == "/")
		{
			corespondingarray[CountOfVariables - 1] = LHS_Of_Arithmaticoperator_In_caseOfValue / corespondingarray[RHSindex];
		}
	}
	else if (checkLHS == true && checkRHS == true)
	{
		if (Arithmaticoperator == "+")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] + corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "-")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] - corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "*")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[RHSindex] * corespondingarray[LHSindex];
		}
		else if (Arithmaticoperator == "/")
		{
			corespondingarray[CountOfVariables - 1] = corespondingarray[LHSindex] / corespondingarray[RHSindex];
		}
	}

}


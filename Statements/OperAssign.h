#pragma once
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class OperAssign : public Statement
{
private:
	string LHS;
	string LHS_Of_Arithmaticoperator;
	string RHS_Of_Arithmaticoperator;
	string Arithmaticoperator;
	Connector* pOutConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	/*****************************/
	double LHS_Of_Arithmaticoperator_In_caseOfValue;
	bool IsTheRHSValue;
	double RHS_Of_Arithmaticoperator_In_caseOfValue;
	bool IsTheLHSValue;
	/********************************************/
	virtual void UpdateStatementText();
	// x = 5 + 5
public:
	OperAssign(Point Lcorner, string LeftHS = "", string RightHSOfAO = "" , string LEFTHSOfAO = "", string AO = "");
	string getRightHSOfAO();
	string getLHS();
	string getLHSofAO();
	void setLHS(const string& L);
	void setRightHSOfAO(string R);
	void setAO(string ao);
	void setLEFTHSOfAO(string La);
	Point getInlet();
	Point getOutlet(int x = 0);
	bool Is_In_Region(Point& p1);
	virtual void Draw(Output* pOut) const;
	void SetConnector(Connector* pOutConn);
	Connector* GetConnector(int checker = 0);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	void Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& CountOfVariables, Output* pOut, int writecount);
};


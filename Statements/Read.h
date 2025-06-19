#pragma once
#include "../Statements/Statement.h"
#include "../GUI/UI_Info.h"
#include <sstream>
class Read :public Statement
{
	Connector* pOutConn;
	Point Inlet;
	Point Outlet;
	Point Center;
	string variable_name;
	double value;
public:
	Read(Point corner, string text, double value);
	void Draw(Output* pOut) const;
	virtual void UpdateStatementText();
	virtual Point getInlet();
	virtual Point getOutlet(int x = 0);
	bool Is_In_Region(Point& p1);
	void SetConnector(Connector* pOutConn);
	Connector* GetConnector(int checker = 0);
	double GetValue();
	string GetVariableName();
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& OutFile);

	void SimulateRead(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, Input* pIn,int writecount);
};


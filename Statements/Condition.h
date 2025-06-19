#ifndef CONDITION_H
#define CONDITION_H

#include "../Statements/Statement.h"
#include "../HelperFn.h"
#include "../Actions/Run.h"

class Condition : public Statement
{
private:
	string RHS;
	string LHS;
	string CompOperator;

	Connector* pOutConnTrue;
	Connector* pOutConnFalse;

	Point Inlet;
	Point OutletTrue, OutletFalse;
	Point UpperPoint;

	virtual void UpdateStatementText();

public:
	Condition(Point UPpoint, string LeftHS = "", string ComparisonOperator = "", string RightHS = "");

	void setCompOperator(const string& C);

	void setLHS(const string& L);

	void setRHS(const string& R);

	Point getOutlet(int x =0);

	Point getInlet();

	Point getOutletTrue();

	Point getOutletFalse();

	string getLHS();

	string getRHS();

	string getCompOperator();

	virtual void Draw(Output* pOut) const;

	virtual bool Is_In_Region(Point& p1);

	void SetConnector(Connector* Connout);

	Connector* GetConnector(int checker = 0);

	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);

	bool ConditionTrueOrFalse(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, int writecount = 0);

	~Condition();

};

#endif

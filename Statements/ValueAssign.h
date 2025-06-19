#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pOutConn;	//Value Assignment Stat. has one Connector to next statement
	                        //Each statement type in flowchart has a predefined number of (output) connectors
	                        //For example, conditional statement always has 2 output connectors

	                        //Note: We don't need to keep track with input connectors
	                        //      Whenever we want to iterate on all statements of the flowchart
	                        //      we will begin with start statement then its output connector
	                        //      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	

	ValueAssign(Point Lcorner, string LeftHS="", double RightHS=0);

	void setLHS(const string &L);

	void setRHS(double R);

	Point getInlet();

	string getLHS();
	double getRHS();

	virtual void Draw(Output* pOut) const;

	bool Is_In_Region(Point& p1);

	Point getOutlet(int x = 0);

	void SetConnector(Connector* pOutConn);

	Connector* GetConnector(int checker = 0);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);

	virtual void Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, int writecount = 0);


	~ValueAssign();
};

#endif

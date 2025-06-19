#pragma once
#ifndef START_H
#define START_H

#include "Statement.h"


class Start : public Statement
{
private:
	Connector* pOutConn;

	//Value Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	Point Outlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors

	Point Center;	//Center of the statement block.

	virtual void UpdateStatementText();

public:

	Start(Point Center);

	virtual void Draw(Output* pOut) const;

	~Start();

	Point getOutlet(int x = 0);

	Point getInlet();

	virtual void SetConnector(Connector* pOutConn);

	Connector* GetConnector(int checker = 0);

	virtual bool Is_In_Region(Point& p1);

	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
};
#endif

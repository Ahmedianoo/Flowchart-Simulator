#pragma once
#ifndef END_H
#define END_H

#include "Statement.h"


class End : public Statement 
{
private:
	Point Inlet;

	Point Center;	//Center of the statement block.

	virtual void UpdateStatementText();

public:

	End(Point Center);

	Point getOutlet(int x = 0);

	Point getInlet();

	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);


	~End();

	virtual bool Is_In_Region(Point& p1);

	void SetConnector(Connector* pOutConn);

	Connector* GetConnector(int checker);

};
#endif

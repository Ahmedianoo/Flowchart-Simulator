#ifndef SELECT_H
#define SELECT_H

#include "..\ApplicationManager.h"
#include "Action.h"
class Select : public Action
{
private:
	int ID;
	Point Position;
	Statement* S;
	Connector* C;

public:

	Select(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
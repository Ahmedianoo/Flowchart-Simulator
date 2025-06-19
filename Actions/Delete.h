#ifndef DELETE_H
#define DELETE_H

#include "..\ApplicationManager.h"
#include "Action.h"
class Delete : public Action
{
private:
	Statement* S;
	Connector* C;

public:
	Delete(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
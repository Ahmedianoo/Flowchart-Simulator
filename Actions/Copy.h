#ifndef COPY_H
#define COPY_H

#include "Action.h"
#include "../Statements/Statement.h"

class Copy : public Action
{
private:
	Statement* CopiedStat;


public:
	Copy(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif

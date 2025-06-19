#ifndef Paste_H
#define Paste_H
#include "Action.h"
#include "../Statements/Statement.h"

class Paste : public Action
{
private:
	Statement* PastedStat;
	Point newPosition;

public:

	Paste(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif
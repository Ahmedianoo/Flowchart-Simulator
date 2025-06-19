#ifndef ADD_CONDITION_H
#define ADD_CONDITION_H

#include "..\ApplicationManager.h"
#include "..\Actions/Action.h"
#include "..\Statements\Condition.h"
class AddCondition : public Action
{
private:
	Point Position;
	string LHS;
	string RHS;
	string CompOperator;

public:
	AddCondition(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif
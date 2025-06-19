#pragma once
#ifndef ADD_OPERATOR_ASSIGN_H
#define ADD_OPERATOR_ASSIGN_H
#include "Action.h"
#include "..\ApplicationManager.h"
class AddOperAssign : public Action
{
private:
	Point Position;
	string LHS;
	string LHS_Of_Arithmaticoperator;
	string RHS_Of_Arithmaticoperator;
	string Arithmaticoperator;
public:
	AddOperAssign(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif
#pragma once
#ifndef ADD_VARIABLE_ASSIGN_H
#define ADD_VARIABLE_ASSIGN_H
#include "Action.h"
#include <iostream>
#include "..\Statements\VariableAssign.h"

class AddVariableAssign : public Action
{
private:

	Point Position;
	string LHS;
	string RHS;
public:
	AddVariableAssign(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif
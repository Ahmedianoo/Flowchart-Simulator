#pragma once
#include "Action.h"
#include <WinUser.h>
class AddWrite :public Action
{
	string print;
	Point Position;
	double Value;
	string userinput;
public:
	AddWrite(ApplicationManager* pAppManager);
	void Execute();
	void ReadActionParameters();
};

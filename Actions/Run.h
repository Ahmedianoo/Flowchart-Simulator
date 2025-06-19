#pragma once
#include "../ApplicationManager.h"
#include "../Statements/Statement.h"
#include "../Connector.h"

class Condition;

class Run
{
private:
	ApplicationManager* pManager;
	Statement** Statlist;
	Connector** ConnList;
	int ConnCount;
	int statcount;
	string ArrayofIntializedVariables[200];
	double CorrespondingValuesforVariables[200];
	int CountOfVariables;
public:
	Run(Statement* Statlis[], int c, Connector* connlist[], int cc, ApplicationManager* pAppManager);
	void operate();
	void OperateOnBranches(bool trueorfalse, Condition* last, int countofwritestatments);
};


#pragma once
#include "Statements/Statement.h"
#include "ApplicationManager.h"
#include "Connector.h"
#include "Statements/Condition.h"
class ValidateOper
{
private:
	ApplicationManager* pManager;
	Statement** Statlist;
	Connector** ConnList;
	int ConnCount;
	int statcount;
	int checkofstart_end = 0;
	int CheckIfFulandCoore = 0;
	int CheckofOutConne = 0;
public:
	//Statement* Statlis[], int c
	//ApplicationManager* pAppManager) :Action(pAppManager)
	ValidateOper(Statement* Statlis[], int c, Connector* connlist[], int cc, ApplicationManager* pAppManager);
	bool CountNumberOfStart_End();
	bool CheckIfFullyandCorrectlyConnected();
	bool CheckofOutputConnectors();
	bool CheckForVariablesIntilization();
	void Checkbranches(string(&arrayofintializedvariables)[200], int copiedvariablescount, Point tostartfrom, int alreadydoneconnectors, Condition* last, bool trueorfalse);

};


#include "Run.h"
#include "../Statements/Start.h"
#include "../Statements/ValueAssign.h"
#include "../Statements/VariableAssign.h"
#include "../Statements/OperAssign.h"
#include "../Statements/Read.h"
#include "../Statements/Write.h"
#include "../Statements/Condition.h"
#include "../Statements/End.h"
#include "../Statements/Condition.h"

Run::Run(Statement* Statlis[], int c, Connector* connlist[], int cc, ApplicationManager* pAppManager)
{

	Statlist = Statlis;
	statcount = c;
	pManager = pAppManager;
	ConnList = connlist;
	ConnCount = cc;
}

void Run::operate()
{
	int CountOfVariables = 0;
	int writecount = 0;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Statement* copy1;
	Statement* test1;
	int count = -1;
	bool checkIfExist = false;
	int startID;
	int step = 0;
	for (int i = 0; i < statcount; i++)
	{
		test1 = dynamic_cast<Start*>(Statlist[i]);
		if (test1 != NULL) {
			copy1 = Statlist[i];
			startID = Statlist[i]->GetID();
			Statlist[i] = Statlist[i];
			break;
		}
	}
	Point dummy;
	Statement* copy;
	Connector* currentconnector;
	Statement* test;
	Condition* testcondition;
	for (int i = 0; i < ConnCount; i++)
	{
		count++;
		bool sure = false;
		if (step == 0)
		{
			/*for (int j = 0; j < ConnCount; j++)
			{
				if (copy1->GetID() == ConnList[j]->getSrcStat()->GetID())
				{
					currentconnector = ConnList[j];
				}
			}*/
			copy = copy1;
			step++;
		}
		else
		{
			for (int j = 0; j < ConnCount; j++)
			{
				if (copy->GetID() == ConnList[j]->getSrcStat()->GetID())
				{
					currentconnector = ConnList[j];
				}
			}
			copy = currentconnector->getDstStat();
		}


		if (copy != NULL) {
			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL)
			{
				((Read*)test)->SimulateRead(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut, pIn, 0);
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut, writecount);
				writecount++;
			}

			testcondition = dynamic_cast<Condition*>(copy);
			if (testcondition != NULL)
			{
				bool check;
				check = testcondition->ConditionTrueOrFalse(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
				if (check == true)
				{
					OperateOnBranches(true, testcondition, writecount);
				}
				else
				{
					OperateOnBranches(false, testcondition, writecount);
				}
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL)
			{
				return;
			}

		}
	}
}

void Run::OperateOnBranches(bool trueorfalse, Condition* last, int countofwritestatments)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Condition* testcondition;

	Statement* copy = last;
	Connector* currentconnector;
	Statement* test;
	int writecount = countofwritestatments;
	if (trueorfalse == true)
	{
		for (int j = 0; j < ConnCount; j++)
		{
			if ((last->getOutletTrue().x == ConnList[j]->getStartPoint().x) && (last->getOutletTrue().y == ConnList[j]->getStartPoint().y))
			{
				copy = ConnList[j]->getDstStat();
			}
		}
	}
	else
	{
		for (int j = 0; j < ConnCount; j++)
		{
			if ((last->getOutletFalse().x == ConnList[j]->getStartPoint().x) && (last->getOutletFalse().y == ConnList[j]->getStartPoint().y))
			{
				copy = ConnList[j]->getDstStat();
			}
		}
	}
	int step = 0;
	bool checkIfExist = false;

	int count = -1;

	for (int i = 0; i < (ConnCount); i++)
	{
		count++;
		bool sure = false;
		if (step != 0)
		{
			for (int j = 0; j < ConnCount; j++)
			{
				if (copy->GetID() == ConnList[j]->getSrcStat()->GetID())
				{
					currentconnector = ConnList[j];
				}
			}
			copy = currentconnector->getDstStat();
		}
		step++;


		if (copy != NULL) {

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}
			test = dynamic_cast<Read*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL)
			{
				test->Simulate(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut, writecount);
				writecount++;
			}

			testcondition = dynamic_cast<Condition*>(copy);
			if (testcondition != NULL)
			{
				bool check;
				check = testcondition->ConditionTrueOrFalse(ArrayofIntializedVariables, CorrespondingValuesforVariables, CountOfVariables, pOut);
				if (check == true)
				{
					OperateOnBranches(true, testcondition, writecount);
				}
				else
				{
					OperateOnBranches(false, testcondition, writecount);
				}
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL)
			{
				return;
			}
		}



	}
}

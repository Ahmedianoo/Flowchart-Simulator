#include "ValidateOper.h"
#include "Statements/Start.h"
#include "Statements/End.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "Statements/Condition.h"
#include "Statements/OperAssign.h"
#include "Statements/ValueAssign.h"
#include "Statements/VariableAssign.h"
#include "Statements/Read.h"
#include "Statements/Write.h"

ValidateOper::ValidateOper(Statement* Statlis[], int c, Connector* connlist[], int cc, ApplicationManager* pAppManager)
{
	Statlist = Statlis;
	statcount = c;
	pManager = pAppManager;
	ConnList = connlist;
	ConnCount = cc;
}

bool ValidateOper::CountNumberOfStart_End()
{
	bool check = true;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point dummy;
	Statement* copy;
	Statement* test;
	int Number_of_StartStatments = 0;
	int Number_of_EndStatments = 0;
	for (int i = 0; i < statcount; i++)
	{
		copy = Statlist[i];
		if (copy != NULL) {
			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				Number_of_StartStatments++;
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL) {
				Number_of_EndStatments++;
			}
		}
	}
	if (Number_of_StartStatments != 1)
	{
		pOut->PrintMessage("Error the chart must have exactly one Start statment,click to continue");
		pIn->GetPointClicked(dummy);
		check = false;
	}
	if (Number_of_EndStatments != 1)
	{
		pOut->PrintMessage("Error the chart must have exactly one End statment,click to continue");
		pIn->GetPointClicked(dummy);
		check = false;
	}
	if (check == true)
	{
		checkofstart_end = 1;
	}
	else
	{
		checkofstart_end = 0;
	}
	return check;
}

bool ValidateOper::CheckIfFullyandCorrectlyConnected()
{
	bool check = true;
	int Number_of_Supposed_Outlet_Points = 0;
	int Number_of_Actual_Outlet_Points = 0;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point dummy;
	Statement* copy;
	Statement* test;
	int Number_of_StartStatments = 0;
	for (int i = 0; i < statcount; i++)
	{
		copy = Statlist[i];
		if (copy != NULL) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points = Number_of_Supposed_Outlet_Points + 2;
			}
			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				Number_of_Supposed_Outlet_Points++;
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points++;
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points++;
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points++;
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points++;
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL)
			{
				Number_of_Supposed_Outlet_Points++;
			}
		}
	}
	if (Number_of_StartStatments == 1)
	{
		Number_of_Supposed_Outlet_Points++;
	}


	for (int i = 0; i < ConnCount; i++)
	{
		copy = ConnList[i]->getSrcStat();
		if (copy != NULL) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points = Number_of_Actual_Outlet_Points + 1;
			}
			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				Number_of_Actual_Outlet_Points++;
			}
			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points++;
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points++;
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points++;
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points++;
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL)
			{
				Number_of_Actual_Outlet_Points++;
			}
		}
	}
	if (Number_of_StartStatments == 1)
	{
		Number_of_Actual_Outlet_Points++;
	}
	if (Number_of_Actual_Outlet_Points == Number_of_Supposed_Outlet_Points && checkofstart_end == 1)
	{
		pOut->PrintMessage("the chart is fully connected ,click to continue");
		pIn->GetPointClicked(dummy);

	}
	else if (Number_of_Actual_Outlet_Points > Number_of_Supposed_Outlet_Points)
	{
		pOut->PrintMessage("the chart is fully connected but not correctly ,click to continue");
		pIn->GetPointClicked(dummy);
		check = false;
	}
	else if (Number_of_Actual_Outlet_Points < Number_of_Supposed_Outlet_Points)
	{
		pOut->PrintMessage("the chart is neither connected nor correct ,click to continue");
		pIn->GetPointClicked(dummy);
		check = false;
	}
	else if (Number_of_Actual_Outlet_Points == Number_of_Supposed_Outlet_Points && checkofstart_end == 0)
	{
		pOut->PrintMessage("the chart is fully connected but not correctly ,click to continue");
		pIn->GetPointClicked(dummy);
		check = false;
	}
	if (check == true)
	{
		CheckIfFulandCoore = 1;
	}
	else
	{
		CheckIfFulandCoore = 0;
	}
	return check;
}

bool ValidateOper::CheckofOutputConnectors()
{
	bool check = true;
	Point dummy;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	int* outconnectorcount;
	outconnectorcount = new int[statcount];
	for (int i = 0; i < statcount; i++)
	{
		outconnectorcount[i] = 0;
	}

	Statement* copy;
	Statement* test;
	for (int i = 0; i < ConnCount; i++)
	{
		copy = ConnList[i]->getSrcStat();
		if (copy != NULL) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}

			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				outconnectorcount[ConnList[i]->getSrcStat()->GetID()]++;
			}
		}
	}

	for (int i = 0; i < statcount; i++)
	{
		copy = Statlist[i];
		if (copy != NULL) {
			test = dynamic_cast<Condition*>(copy);
			if (test != NULL)
			{
				if (outconnectorcount[Statlist[i]->GetID()] != 2)
				{
					pOut->PrintMessage("see this Oper Assign statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pOut->PrintMessage("click to continue");
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}
			}

			test = dynamic_cast<OperAssign*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Oper Assign statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pOut->PrintMessage("click to continue");
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}
			}

			test = dynamic_cast<ValueAssign*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Value Assign statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}

			}

			test = dynamic_cast<VariableAssign*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Variable Assign statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}

			}

			test = dynamic_cast<Read*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Read statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}

			}

			test = dynamic_cast<Write*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Write statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}

			}



			test = dynamic_cast<Start*>(copy);
			if (test != NULL) {
				if (outconnectorcount[Statlist[i]->GetID()] != 1)
				{
					pOut->PrintMessage("see this Start statment has wrong number of output connectors,click to continue");
					Statlist[i]->SetSelected(true);
					Statlist[i]->Draw(pOut);
					pIn->GetPointClicked(dummy);
					Statlist[i]->SetSelected(false);
					Statlist[i]->Draw(pOut);
					check = false;
				}
			}


		}
	}
	if (check == true)
	{
		CheckofOutConne = 1;
	}
	else
	{
		CheckofOutConne = 0;
	}

	return check;


}

bool ValidateOper::CheckForVariablesIntilization()
{
	bool thereturn = true;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string arrayofintializedvariables[200];
	Statement* copy1;
	Statement* test1;
	int count = -1;
	bool checkIfExist = false;
	int startID;
	int step = 0;
	for (int i = 0; i < statcount; i++)
	{
		copy1 = Statlist[i];

		test1 = dynamic_cast<Start*>(copy1);
		if (test1 != NULL) {
			startID = copy1->GetID();
			break;
		}
	}
	Point dummy;
	Statement* copy;
	Connector* currentconnector;
	Statement* test;
	ValueAssign* testValueAssign;
	Condition* testCondition;
	Read* testRead;
	VariableAssign* testvariableAssign;
	OperAssign* testoperAssign;
	Write* testWrite;
	int CountOfVariables = 0;
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

			testValueAssign = dynamic_cast<ValueAssign*>(copy);
			if (testValueAssign != NULL) {
				arrayofintializedvariables[CountOfVariables] = testValueAssign->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofintializedvariables[k] == testValueAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofintializedvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}
			}

			testvariableAssign = dynamic_cast<VariableAssign*>(copy);
			if (testvariableAssign != NULL) {
				arrayofintializedvariables[CountOfVariables] = testvariableAssign->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofintializedvariables[k] == testvariableAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofintializedvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}

				for (int i = 0; i < CountOfVariables; i++)
				{
					if (testvariableAssign->getRHS() == arrayofintializedvariables[i])
					{
						sure = true;
						break;
					}
				}
				if (sure == false)
				{
					thereturn = false;
					pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
					testvariableAssign->SetSelected(true);
					testvariableAssign->Draw(pOut);
					pIn->GetPointClicked(dummy);
					testvariableAssign->SetSelected(false);
					testvariableAssign->Draw(pOut);

				}
				sure = false;
			}

			testoperAssign = dynamic_cast<OperAssign*>(copy);
			if (testoperAssign != NULL)
			{
				arrayofintializedvariables[CountOfVariables] = testoperAssign->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofintializedvariables[k] == testoperAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofintializedvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}

				if (IsVariable(testoperAssign->getLHSofAO()) == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testoperAssign->getLHSofAO() == arrayofintializedvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						thereturn = false;
						pOut->PrintMessage("the LHS of the Arithmatic operator in this statment is unintiliazed,click to continue");
						testoperAssign->SetSelected(true);
						testoperAssign->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testoperAssign->SetSelected(false);
						testoperAssign->Draw(pOut);

					}
					sure = false;
				}
				sure = false;
				if (IsVariable(testoperAssign->getRightHSOfAO()) == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testoperAssign->getRightHSOfAO() == arrayofintializedvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						thereturn = false;
						pOut->PrintMessage("the RHS of the Arithmatic operator in this statment is unintiliazed,click to continue");
						testoperAssign->SetSelected(true);
						testoperAssign->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testoperAssign->SetSelected(false);
						testoperAssign->Draw(pOut);

					}
					sure = false;
				}
				sure = false;

			}



			testRead = dynamic_cast<Read*>(copy);
			if (testRead != NULL)
			{
				arrayofintializedvariables[CountOfVariables] = testRead->GetVariableName();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofintializedvariables[k] == testRead->GetVariableName())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofintializedvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}
			}

			testWrite = dynamic_cast<Write*>(copy);
			if (testWrite != NULL)
			{
				if (testWrite->IsWriteVariable() == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testWrite->GetPrint() == arrayofintializedvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						thereturn = false;
						pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
						testWrite->SetSelected(true);
						testWrite->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testWrite->SetSelected(false);
						testWrite->Draw(pOut);

					}
					sure = false;
				}
			}

			testCondition = dynamic_cast<Condition*>(copy);
			if (testCondition != NULL)
			{
				if (IsVariable(testCondition->getLHS()))
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testCondition->getLHS() == arrayofintializedvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						thereturn = false;
						pOut->PrintMessage("the LHS Variable in this statment is unintiliazed,click to continue");
						testCondition->SetSelected(true);
						testCondition->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testCondition->SetSelected(false);
						testCondition->Draw(pOut);

					}
					sure = false;
				}


				if (IsVariable(testCondition->getRHS()))
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testCondition->getRHS() == arrayofintializedvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						thereturn = false;
						pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
						testCondition->SetSelected(true);
						testCondition->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testCondition->SetSelected(false);
						testCondition->Draw(pOut);

					}
					sure = false;
				}

				//CHECK FOR THE TRUE BRANCH
				Checkbranches(arrayofintializedvariables, CountOfVariables, testCondition->getOutletTrue(), count, testCondition, true);
				//CHECK FOR THE FALSE BRANCH
				Checkbranches(arrayofintializedvariables, CountOfVariables, testCondition->getOutletFalse(), count, testCondition, false);

				return thereturn;
			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL) {
				return thereturn;
			}

		}
	}

	return thereturn;
}

void ValidateOper::Checkbranches(string(&arrayofintializedvariables)[200], int copiedvariablescount, Point tostartfrom, int alreadydoneconnectors, Condition* last, bool trueorfalse)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string arrayofvariables[200];
	Statement* copy = last;

	for (int i = 0; i < copiedvariablescount; i++)
	{
		arrayofvariables[i] = arrayofintializedvariables[i];
	}

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
	Point dummy;
	Connector* currentconnector;
	Statement* test;
	ValueAssign* testValueAssign;
	Condition* testCondition;
	Read* testRead;
	VariableAssign* testvariableAssign;
	OperAssign* testoperAssign;
	Write* testWrite;
	int CountOfVariables = copiedvariablescount;
	for (int i = 0; i < (ConnCount - alreadydoneconnectors); i++)
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
			if (test != NULL) {
				arrayofvariables[CountOfVariables] = ((ValueAssign*)test)->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofvariables[k] == testValueAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}
			}

			testvariableAssign = dynamic_cast<VariableAssign*>(copy);
			if (testvariableAssign != NULL) {
				arrayofvariables[CountOfVariables] = testvariableAssign->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofvariables[k] == testvariableAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}

				for (int i = 0; i < CountOfVariables; i++)
				{
					if (testvariableAssign->getRHS() == arrayofvariables[i])
					{
						sure = true;
						break;
					}
				}
				if (sure == false)
				{
					pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
					testvariableAssign->SetSelected(true);
					testvariableAssign->Draw(pOut);
					pIn->GetPointClicked(dummy);
					testvariableAssign->SetSelected(false);
					testvariableAssign->Draw(pOut);

				}
				sure = false;
			}

			testoperAssign = dynamic_cast<OperAssign*>(copy);
			if (testoperAssign != NULL)
			{
				arrayofvariables[CountOfVariables] = testoperAssign->getLHS();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofvariables[k] == testoperAssign->getLHS())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}

				if (IsVariable(testoperAssign->getLHSofAO()) == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testoperAssign->getLHSofAO() == arrayofvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						pOut->PrintMessage("the LHS of the Arithmatic operator in this statment is unintiliazed,click to continue");
						testoperAssign->SetSelected(true);
						testoperAssign->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testoperAssign->SetSelected(false);
						testoperAssign->Draw(pOut);

					}
					sure = false;
				}
				sure = false;
				if (IsVariable(testoperAssign->getRightHSOfAO()) == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testoperAssign->getRightHSOfAO() == arrayofvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						pOut->PrintMessage("the RHS of the Arithmatic operator in this statment is unintiliazed,click to continue");
						testoperAssign->SetSelected(true);
						testoperAssign->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testoperAssign->SetSelected(false);
						testoperAssign->Draw(pOut);

					}
					sure = false;
				}
				sure = false;

			}



			testRead = dynamic_cast<Read*>(copy);
			if (testRead != NULL)
			{
				arrayofvariables[CountOfVariables] = testRead->GetVariableName();
				CountOfVariables++;
				for (int k = 0; k < CountOfVariables - 1; k++)
				{
					if (arrayofvariables[k] == testRead->GetVariableName())
					{
						checkIfExist = true;
					}
				}
				if (checkIfExist == true)
				{
					arrayofvariables[CountOfVariables] = "";
					CountOfVariables--;
				}
				else
				{
					checkIfExist = false;
				}
			}

			testWrite = dynamic_cast<Write*>(copy);
			if (testWrite != NULL)
			{
				if (testWrite->IsWriteVariable() == true)
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testWrite->GetPrint() == arrayofvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
						testWrite->SetSelected(true);
						testWrite->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testWrite->SetSelected(false);
						testWrite->Draw(pOut);

					}
					sure = false;
				}
			}

			testCondition = dynamic_cast<Condition*>(copy);
			if (testCondition != NULL)
			{
				if (IsVariable(testCondition->getLHS()))
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testCondition->getLHS() == arrayofvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						pOut->PrintMessage("the LHS Variable in this statment is unintiliazed,click to continue");
						testCondition->SetSelected(true);
						testCondition->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testCondition->SetSelected(false);
						testCondition->Draw(pOut);

					}
					sure = false;
				}


				if (IsVariable(testCondition->getRHS()))
				{
					for (int i = 0; i < CountOfVariables; i++)
					{
						if (testCondition->getRHS() == arrayofvariables[i])
						{
							sure = true;
							break;
						}
					}
					if (sure == false)
					{
						pOut->PrintMessage("the RHS Variable in this statment is unintiliazed,click to continue");
						testCondition->SetSelected(true);
						testCondition->Draw(pOut);
						pIn->GetPointClicked(dummy);
						testCondition->SetSelected(false);
						testCondition->Draw(pOut);

					}
					sure = false;
				}
				//CHECK FOR THE TRUE BRANCH
				Checkbranches(arrayofvariables, CountOfVariables, testCondition->getOutletTrue(), count, testCondition, true);
				//CHECK FOR THE FALSE BRANCH
				Checkbranches(arrayofvariables, CountOfVariables, testCondition->getOutletFalse(), count, testCondition, false);

			}

			test = dynamic_cast<End*>(copy);
			if (test != NULL) {
				return;
			}

		}
	}
}










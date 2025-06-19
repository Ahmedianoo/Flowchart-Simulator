#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions/AddConnector.h"
#include "Actions\AddCondition.h"
#include "Actions\AddEnd.h"
#include "Actions\AddOperAssign.h"
#include "Actions\AddVariableAssign.h"
#include "Actions\AddStart.h"
#include "Actions\AddValueAssign.h"
#include "Actions/Select.h"
#include "Actions/Delete.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Actions/Run.h"
#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"
#include "Actions/Copy.h"
#include "Actions/Paste.h"
#include "Statements/Read.h"
#include "Statements/Write.h"
#include "Statements/OperAssign.h"
#include "ValidateOper.h"


//Constructor

ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	ConSelected = NULL;

	//Create an array of Statement pointers and set them to NULL		
	for (int i = 0; i < MaxCount; i++)
	{
		StatList[i] = NULL;
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	Point P;
	//According to ActioType, create the corresponding action object
	if (UI.AppMode == DESIGN)
	{
		switch (ActType)
		{
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_END:
			pAct = new AddEnd(this);
			break;

		case ADD_START:
			pAct = new AddStart(this);
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVariableAssign(this);
			break;

		case ADD_OPER_ASSIGN:
			pAct = new AddOperAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddCondition(this);
			break;

		case ADD_READ:
			pAct = new AddRead(this);
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;

		case ADD_CONNECTOR:
			if (StatCount < 2)
			{
				pOut->PrintMessage("please , add 2 statements in the drawing area to be able to use the connectors");
			}
			else
			{
				pAct = new AddConnector(this);
			}
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case EDIT_STAT:
			pOut->PrintMessage("Action: edit statement action, Click anywhere");
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case DSN_TOOL:
			pOut->PrintMessage("Action: a click on the Design Tool Bar, Click anywhere");
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case CUT:
			pOut->PrintMessage("Action: cut action, Click anywhere");
			break;

		case PASTE:
			pAct = new Paste(this);
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			break;

		case SWITCH_SIM_MODE:
			UI.AppMode = SIMULATION;
			pOut->CreateSimulationToolBar();
			break;

		case SWITCH_DSN_MODE:
			pOut->PrintMessage("Action: Switch to Design Mode, creating Design tool bar");
			pOut->CreateDesignToolBar();
			break;

		case DRAWING_AREA:
			pOut->PrintMessage("Action: a click on the drawing area, click to continue");
			break;

		case OUTPUT_AREA:
			pOut->PrintMessage("Action: a click on the output area, click to continue");
			break;

		case VALIDATE:
			pOut->PrintMessage("Action: validate, click to continue");
			break;

		case RUN:
			pOut->PrintMessage("Action: run, click to continue");
			break;

		case SIM_TOOL:
			pOut->PrintMessage("Action: a click on the Simulation Tool Bar, Click anywhere");
			break;

		case EXIT:
			break;

		case STATUS:
			return;

		}

	}
	else if (UI.AppMode == SIMULATION)
	{
		switch (ActType)
		{
		case SWITCH_DSN_MODE:
			UI.AppMode = SIMULATION;
			pOut->CreateDesignToolBar();
			break;
		case VALIDATE:
			Validate();
			break;
		case RUN:
			run();
			break;


		}
	}
	//Execute the created action	
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it

	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements

void ApplicationManager::AddStatement(Statement* pStat)
{
	if (StatCount < MaxCount)
	{
		StatList[StatCount] = pStat;
		StatList[StatCount]->setID(StatCount);
		StatCount++;
	}

}
bool ApplicationManager::Validate()
{
	ValidateOper val(StatList, StatCount, ConnList, ConnCount, this);
	bool cond1, cond2, cond3;
	cond1 = val.CountNumberOfStart_End();
	cond2 = val.CheckIfFullyandCorrectlyConnected();
	cond3 = val.CheckofOutputConnectors();

	if (cond1 == true && cond2 == true && cond3 == true)
	{
		pOut->PrintMessage("check for variables");
		val.CheckForVariablesIntilization();
		return true;
	}
	else
	{
		return false;
	}
}


void ApplicationManager::run()
{
	if (Validate() == true)
	{
		pOut->ClearOutputBar();
		Run r1(StatList, StatCount, ConnList, ConnCount, this);
		r1.operate();
	}
	else
	{
		pOut->PrintMessage("you cannot run until there are no complilation errors");
	}

}

int ApplicationManager::GetStatCount() const
{
	return StatCount;
}

int ApplicationManager::GetConnectorCount() const
{
	return ConnCount;
}

void ApplicationManager::AddConn(Connector* pConn)
{
	ConnList[ConnCount] = pConn;
	pConn->setID(ConnCount);
	ConnCount++;
}

void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for (int i = 0; i < StatCount; i++)
		if (StatList[i] != NULL)
			StatList[i]->Draw(pOut);

	//Draw all connections
	for (int i = 0; i < ConnCount; i++)
		if (ConnList[i] != NULL)
			ConnList[i]->Draw(pOut);

}

void ApplicationManager::RemoveStatement(int x)
{
	for (int i = x; i < StatCount; i++)
	{
		if (x != StatCount - 1)
		{
			StatList[x] = StatList[x + 1];
			if (StatList[i] != NULL)
			{
				StatList[i]->setID(i);
			}
		}
		else
		{
			StatList[x] = NULL;
		}
	}
	UpdateInterface();
	StatCount--;
}

Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->Is_In_Region(P) == true)
		{
			return ConnList[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->Is_In_Region(P) == true)
		{
			return StatList[i];
		}
	}
	return NULL;
}

Statement* ApplicationManager::GetStatementIteration(int i)
{
	if (i < StatCount)
	{
		return StatList[i];
	}
	return NULL;
}

Connector* ApplicationManager::GetConnIteration(int i)
{
	if (i < ConnCount)
	{
		return ConnList[i];
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement* ApplicationManager::GetSelectedStatement() const
{
	return pSelectedStat;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement* pStat)
{
	if (pSelectedStat != NULL)
	{
		pSelectedStat->SetSelected(false);
	}
	if (ConSelected != NULL)
	{
		ConSelected->SetSelected(false);
	}
	if (pSelectedStat == pStat)
	{
		pSelectedStat = NULL;
	}
	pSelectedStat = pStat;
	if (pSelectedStat != NULL)
	{
		pSelectedStat->SetSelected(true);
	}
}

Connector* ApplicationManager::GetSelectedCon() const
{
	return ConSelected;
}

void ApplicationManager::SetSelectedCon(Connector* pCon)
{
	if (pSelectedStat != NULL)
	{
		pSelectedStat->SetSelected(false);
	}
	if (ConSelected != NULL)
	{
		ConSelected->SetSelected(false);
	}
	if (ConSelected == pCon)
	{
		ConSelected = NULL;
	}
	ConSelected = pCon;
	if (ConSelected != NULL)
	{
		ConSelected->SetSelected(true);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement* ApplicationManager::GetClipboard() const
{
	return pClipboard;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement* pStat)
{
	pClipboard = pStat;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface

void ApplicationManager::RemoveConnector(int x)
{
	for (int i = x; i < ConnCount; i++)
	{
		if (i != ConnCount - 1)
		{
			ConnList[i] = ConnList[i + 1];
			if (ConnList[i] != NULL)
			{
				ConnList[i]->setID(i);
			}
		}
		else
		{
			ConnList[i] = NULL;
		}
	}
	UpdateInterface();
	ConnCount--;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] != NULL)
			delete StatList[i];
	}
	for (int i = 0; i < ConnCount; i++)
	{
		if (StatList[i] != NULL)
			delete ConnList[i];
	}
	delete pIn;
	delete pOut;
}


void ApplicationManager::SaveAll(ofstream& OutFile) {
	OutFile << StatCount << endl;
	for (int i = 0; i < StatCount; i++) {
		StatList[i]->Save(OutFile);
		OutFile << endl;
	}
	OutFile << endl << ConnCount << endl;
	for (int i = 0; i < ConnCount; i++) {
		ConnList[i]->Save(OutFile);
		OutFile << endl;
	}
}
void ApplicationManager::LoadAll(ifstream& Infile) {
	Point ptdummy;
	string strdummy, StatType;
	int value = 0, fileStatCount, fileConnCount, id;
	Infile >> fileStatCount;
	Statement* pstat;
	for (int i = 0; i < fileStatCount; i++) {
		Infile >> StatType >> id >> ptdummy.x >> ptdummy.y;

		if (StatType == "READ") {
			pstat = new Read(ptdummy, strdummy, value);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "WRITE") {
			pstat = new Write(ptdummy, strdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "COND") {
			pstat = new Condition(ptdummy, strdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "END") {
			pstat = new End(ptdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "STRT") {
			pstat = new Start(ptdummy);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "OP_ASSIGN") {
			pstat = new OperAssign(ptdummy, strdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "VAR_ASSIGN") {
			pstat = new VariableAssign(ptdummy, strdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}
		if (StatType == "VAL_ASSIGN") {
			pstat = new ValueAssign(ptdummy, strdummy);
			pstat->setID(id);
			pstat->Load(Infile);
			AddStatement(pstat);
		}

	}
	Infile >> fileConnCount;
	ConnCount = fileConnCount;
	int srcid, dstid;
	Connector* pconn;
	Statement* SrcStat;
	Statement* DstStat;
	int checker;
	for (int i = 0; i < fileConnCount; i++) {
		Infile >> srcid >> dstid >> checker;
		for (int j = 0; j < fileStatCount; j++) {
			if (srcid == StatList[j]->GetID()) {
				SrcStat = StatList[j];
			}
			if (dstid == StatList[j]->GetID()) {
				DstStat = StatList[j];
			}
		}
		pconn = new Connector(SrcStat, DstStat, checker);
		ConnList[i] = pconn;
	}
	UpdateInterface();
};
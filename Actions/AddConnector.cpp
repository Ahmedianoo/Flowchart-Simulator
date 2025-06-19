#include "AddConnector.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/Output.h"
#include "..\Statements\End.h"
#include "..\Statements\Start.h"
#include "..\Statements\Condition.h"
#include "Delete.h"

AddConnector::AddConnector(ApplicationManager* pAppManager) :Action(pAppManager)
{

	s1 = NULL;
	s2 = NULL;

}

void AddConnector::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	Point Position;

	pOut->PrintMessage("Connector : Click on the first delivering statment");
	pIn->GetPointClicked(Position);

	s1 = pManager->GetStatement(Position);

	Statement* test;
	test = dynamic_cast<End*>(s1);

	while (pManager->GetStatement(Position) == NULL || test != NULL)
	{
		pOut->PrintMessage("Please, select on the delivering statment such that it isn't a start statement");
		pIn->GetPointClicked(Position);
		s1 = pManager->GetStatement(Position);
		test = dynamic_cast<End*>(s1);
	}

	s1 = pManager->GetStatement(Position);
	s1->GetConnector();
	x = 0;
	test = dynamic_cast<Condition*>(s1);

	if (test != NULL)
	{
		pOut->PrintMessage("Selected a Condion statement  Enter 1 for true, Enter 2 for false, then click on the conditonal again to continue");
		pIn->GetPointClicked(Position);
		x = int(pIn->GetValue(pOut));
		while (pManager->GetStatement(Position) != s1)
		{
			pOut->PrintMessage("Click on the same conditional to confirm");
			pIn->GetPointClicked(Position);
		}
		while ((x != 1) && (x != 2))
		{
			x = int(pIn->GetValue(pOut));
		}
	}
	pOut->PrintMessage("Successfully made delivering statment, now click on recieveing statment");
	pIn->GetPointClicked(Position);

	s2 = pManager->GetStatement(Position);
	test = dynamic_cast<Start*>(s2);


	while ((pManager->GetStatement(Position) == NULL || pManager->GetStatement(Position) == s1) || test != NULL)
	{
		pOut->PrintMessage("Please, select on the recieveing statment");
		pIn->GetPointClicked(Position);
		s2 = pManager->GetStatement(Position);
		test = dynamic_cast<Start*>(s2);
	}
}

void AddConnector::Execute()
{
	ReadActionParameters();
	Point dummy;
	Connector* C = NULL;
	Connector* pCond = new Connector(s1, s2, x);

	for (int i = 0; i < pManager->GetStatCount(); i++)
	{
		if (pManager->GetStatementIteration(i) != s1 && pManager->GetStatementIteration(i) != s2)
		{
			if (pCond->Is_In_Region(pManager->GetStatementIteration(i)) == true)
			{
				for (int j = 0; j < pManager->GetConnectorCount(); j++)
				{
					if (pManager->GetConnIteration(j)->getDstStat() == pManager->GetStatementIteration(i) || pManager->GetConnIteration(j)->getSrcStat() == pManager->GetStatementIteration(i))
					{
						C = pManager->GetConnIteration(j);
						pManager->RemoveConnector(j);
						delete C;
						C = NULL;
						j--;
					}
				}
				delete pManager->GetStatementIteration(i);
				pManager->RemoveStatement(i);
			}
		}
	}
	pManager->AddConn(pCond);
}
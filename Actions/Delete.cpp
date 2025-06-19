#include "Delete.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/Output.h"

Delete::Delete(ApplicationManager* pAppManager) :Action(pAppManager)
{
	S = NULL;
	C = NULL;
}

void Delete::ReadActionParameters()
{
	S = pManager->GetSelectedStatement();
	if (S == NULL)
	{
		C = pManager->GetSelectedCon();
	}
}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();
	int r = 0;

	ReadActionParameters();

	if (S == NULL && C == NULL)
	{
		pOut->PrintMessage("No Connecotor or Statement is selected");
		return;
	}
	else
	{
		if (S != NULL)
		{
			int x = 0;
			pOut->PrintMessage("Deleting the selected statement");

			for (int i = 0; i < pManager->GetStatCount(); i++)
			{
				if (pManager->GetStatementIteration(i) == S)
				{
					x = i;
					break;
				}
			}
			for (int j = 0; j < pManager->GetConnectorCount(); j++)
			{
				if (pManager->GetConnIteration(j) != NULL)
				{
					if (pManager->GetConnIteration(j)->getDstStat() == S || pManager->GetConnIteration(j)->getSrcStat() == S)
					{
						C = pManager->GetConnIteration(j);
						pManager->RemoveConnector(j);
						delete C;
						C = NULL;
						j--;
					}
				}
			}
			pManager->RemoveStatement(x);
			delete S;
			S = NULL;
			pManager->SetSelectedStatement(NULL);
			return;
		}
		else
		{
			pOut->PrintMessage("Deleting the selected connector");

			for (int i = 0; i < pManager->GetConnectorCount(); i++)
			{
				if (pManager->GetConnIteration(i) == C)
				{
					pManager->RemoveConnector(i);
					break;
				}
			}
			delete C;
			C = NULL;
			pManager->SetSelectedCon(NULL);
			return;
		}
	}
}

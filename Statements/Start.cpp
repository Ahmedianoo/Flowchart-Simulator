#include "Start.h"
#include <fstream>

void Start::Draw(Output* pOut)  const
{
	pOut->DrawStart(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

};

void Start::UpdateStatementText() {};

Start::Start(Point Center)
{
	pOutConn = NULL;
	Text = "START";
	this->Center = Center;
	Outlet.x = Center.x;
	Outlet.y= Center.y + UI.ASSGN_HI / 2;

};

bool Start::Is_In_Region(Point& p1)
{

	if ((p1.x >= (Center.x - UI.ASSGN_WDTH / 2)) && (p1.x <= (Center.x + UI.ASSGN_WDTH / 2)) && (p1.y >= Center.y - UI.ASSGN_HI / 2) && (p1.y <= Center.y + UI.ASSGN_HI / 2))
	{
		return true;
	}
	return false;
}

void Start::SetConnector(Connector* pOutConn)
{
	if (this->pOutConn != NULL)
	{
		delete this->pOutConn;
	}
	this->pOutConn = pOutConn;
}

Connector* Start::GetConnector(int checker)
{
	return pOutConn;
}

Start::~Start()
{
	if (pOutConn != NULL)
	{
		delete pOutConn;
	}
}

Point Start::getOutlet(int x)
{
	return Outlet;
}

Point Start::getInlet()
{
	Point P;
	P.x = 0;
	P.y = 0;
	return P;
}

void Start::Save(ofstream& OutFile) {
	OutFile << "STRT" << " " << ID << " " << Center.x << " " << Center.y;
}
void Start::Load(ifstream& Infile) {
}
#include "End.h"
#include <fstream>

void End::Draw(Output* pOut)  const 
{
	pOut->DrawEnd(Center, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

};

void End::UpdateStatementText() {};

bool End::Is_In_Region(Point& p1)
{

	if ((p1.x >= (Center.x - UI.ASSGN_WDTH / 2)) && (p1.x <= (Center.x + UI.ASSGN_WDTH / 2)) && (p1.y >= Center.y - UI.ASSGN_HI / 2) && (p1.y <= Center.y + UI.ASSGN_HI / 2))
	{
		return true;
	}
	return false;
}

void End::SetConnector(Connector* pOutConn)
{}

Connector* End::GetConnector(int checker)
{
	return nullptr;
}

End::End(Point Center)
{
	Text = "END";
	this->Center = Center;
	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.ASSGN_HI / 2;

};

Point End::getOutlet(int x)
{
	Point P;
	P.x = 0;
	P.y = 0;
	return P;
}

Point End::getInlet()
{
	return Inlet;
}

End::~End()
{

}

void End::Save(ofstream& OutFile) {
	OutFile << "END" << " " << ID << " " << Center.x << " " << Center.y;
}
void End::Load(ifstream& Infile) {

}
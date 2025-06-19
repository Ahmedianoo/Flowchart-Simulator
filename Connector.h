#pragma once

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include "ApplicationManager.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:

	Statement* SrcStat;	//The source statement of the connector
	Statement* DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected;
	int checker;
	int ID;
public:

	Connector::Connector(Statement* Src, Statement* Dst, int x = 0);

	void		setSrcStat(Statement* Src);
	Statement* getSrcStat();

	void		setDstStat(Statement* Dst);
	Statement* getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut) const;

	int GetChecker() const;

	bool Is_In_Region(Point P) const;

	bool Is_In_Region(Statement* P) const;

	void SetSelected(bool truth);

	bool GetSelected();

	void setID(int id);

	int GetID() const;
	void Save(ofstream& OutFile);

	~Connector();
};

#endif
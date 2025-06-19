#pragma once
#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"


//class Output;
#include "..\GUI\Output.h"
//Base class for all Statements
class Connector;

class Statement
{
protected:

	int ID;			//Each Statement has an ID --> must be unique

	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)

	bool Selected;	//true if the statement is selected on the folwchart

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:

	Statement();

	virtual Point getInlet() = 0;

	virtual Point getOutlet(int x = 0) = 0;

	void SetSelected(bool s);

	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement

	virtual bool Is_In_Region(Point & p1) = 0;

	virtual void setID(int id);

	virtual int GetID() const;

	virtual void SetConnector(Connector* Connout) = 0;

	virtual Connector* GetConnector(int checker = 0) = 0;

	virtual bool GetSelected();

	virtual void Simulate(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, int writecount = 0);

	virtual ~Statement();

	virtual void Save(ofstream& OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream& Infile) = 0;	//Load the Statement parameters from a file


	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	//virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	//virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	//virtual void Edit() = 0;		//Edit the Statement parameter

	//virtual void Simulate();	//Execute the statement in the simulation mode

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

};

#endif

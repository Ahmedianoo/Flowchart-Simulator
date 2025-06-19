#include "Condition.h"
#include "..\Connector.h"
#include "../HelperFn.h"
#include <sstream>

using namespace std;

Condition::Condition(Point UPpoint, string LeftHS, string ComparisonOperator, string RightHS) {
	LHS = LeftHS;
	RHS = RightHS;
	CompOperator = ComparisonOperator;

	UpdateStatementText();

	UpperPoint = UPpoint;

	pOutConnTrue = NULL;	
	pOutConnFalse = NULL;

	Inlet.x = UpperPoint.x;
	Inlet.y = UpperPoint.y;

	OutletTrue.x = UpperPoint.x + UI.COND_WDTH / 2;
	OutletTrue.y = UpperPoint.y + UI.COND_HI / 2;

	OutletFalse = UpperPoint.x - UI.COND_WDTH / 2;
	OutletFalse.y = UpperPoint.y + UI.COND_HI / 2;
}

void Condition::setLHS(const string& R) {
	RHS = R;
	UpdateStatementText();
}

void Condition::setCompOperator(const string& C) {
	CompOperator = C;
	UpdateStatementText();
}

void Condition::setRHS(const string& R) {
	RHS = R;
	UpdateStatementText();
}

void Condition::Draw(Output* pOut) const {
	pOut->DrawCondtionalStat(UpperPoint, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}

void Condition::UpdateStatementText() {
	ostringstream T;
	T << LHS << " " << CompOperator << " " << RHS;
	Text = T.str();
}

bool Condition::Is_In_Region(Point& p1) {
	Point Upper, Lower, Left, Right;
	Upper = UpperPoint;
	Lower.x = Upper.x;
	Lower.y = Upper.y + UI.COND_HI;
	Left.x = Upper.x - UI.COND_WDTH / 2;
	Left.y = Upper.y + UI.COND_HI / 2;
	Right.x = Upper.x + UI.COND_WDTH / 2;
	Right.y = Upper.y + UI.COND_HI / 2;

	if (p1.x < Left.x || p1.x > Right.x || p1.y < Upper.y || p1.y > Lower.y) {
		return false;
	}
	else {
		if (p1.x > Left.x && p1.x < Upper.x && p1.y < Left.y && p1.y > Upper.y) {

			float slopePwithUpper, slopePwithLeft;
			slopePwithUpper = (float)(p1.y - Upper.y) / (float)(p1.x - Upper.x);
			slopePwithLeft = (float)(p1.y - Left.y) / (float)(p1.x - Left.x);

			if (slopePwithLeft < slopePwithUpper) { return false; }
		}
		else if(p1.x > Upper.x && p1.x < Right.x && p1.y > Upper.y && p1.y < Right.y){

			float slopePwithUpper, slopePwithRight;
			slopePwithUpper = (float)(p1.y - Upper.y) / (float)(p1.x - Upper.x);
			slopePwithRight = (float)(p1.y - Right.y) / (float)(p1.x - Right.x);

			if (slopePwithUpper < slopePwithRight) { return false; }
		}
		else if (p1.x > Left.x && p1.x < Lower.x && p1.y > Left.y && p1.y < Lower.y) {

			float slopePwithLeft, slopePwithLower;
			slopePwithLeft = (float)(p1.y - Left.y) / (float)(p1.x - Left.x);
			slopePwithLower = (float)(p1.y - Lower.y) / (float)(p1.x - Lower.x);

			if (slopePwithLower < slopePwithLeft) { return false; }
		}
		else if (p1.x > Lower.x && p1.x < Right.x && p1.y < Lower.y && p1.y > Right.y) {

			float slopePwithLower, slopePwithRight;
			slopePwithLower = (float)(p1.y - Lower.y) / (float)(p1.x - Lower.x);
			slopePwithRight = (float)(p1.y - Right.y) / (float)(p1.x - Right.x);

			if (slopePwithRight < slopePwithLower) { return false; }
		}
	}

	return true;
}

void Condition::SetConnector(Connector* Connout)
{
	if (Connout->GetChecker() == 1)
	{
		pOutConnTrue = Connout;
	}
	else
	{
		pOutConnFalse = Connout;
	}

}

Connector* Condition::GetConnector(int checker)
{
	if (checker == 1)
	{
		return pOutConnTrue;
	}
	else if (checker == 2)
	{
		return pOutConnFalse;
	}
	return nullptr;
}

Point Condition::getInlet() {
	return Inlet;
}

Point Condition::getOutlet(int x)
{
	if (x == 1)
	{
		return getOutletTrue();
	}
	if (x == 2)
	{
		return getOutletFalse();
	}
}

Point Condition::getOutletTrue() {
	return OutletTrue;
}

Point Condition::getOutletFalse() {
	return OutletFalse;
}

Condition::~Condition()
{
	if (pOutConnTrue != NULL)
		delete pOutConnTrue;
	if (pOutConnFalse != NULL)
		delete pOutConnFalse;
}

string Condition::getLHS() {
	return LHS;
}

string Condition::getCompOperator() {
	return CompOperator;
}

string Condition::getRHS() {
	return RHS;
}

void Condition::Save(ofstream& OutFile) {
	OutFile << "COND " << ID << " " << UpperPoint.x << " " << UpperPoint.y << " " << LHS << " ";
	if (CompOperator == "<") {
		OutFile << "LESS";
	}
	if (CompOperator == ">") {
		OutFile << "GRT";
	}
	if (CompOperator == ">=") {
		OutFile << "GRTorEQ";
	}
	if (CompOperator == "==") {
		OutFile << "EQ";
	}
	if (CompOperator == "<=") {
		OutFile << "LESSorEQ";
	}
	OutFile << "  " << RHS;
}
void Condition::Load(ifstream& Infile) {
	Infile >> LHS >> CompOperator >> RHS;
	if (CompOperator == "LESS") {
		CompOperator = "<";
	}
	if (CompOperator == "GRT") {
		CompOperator = ">";
	}
	if (CompOperator == "GRTorEQ") {
		CompOperator = ">=";
	}
	if (CompOperator == "EQ") {
		CompOperator = "==";
	}
	if (CompOperator == "LESSorEQ") {
		CompOperator = "<=";
	}
	UpdateStatementText();
}

bool Condition::ConditionTrueOrFalse(string(&allvariables)[200], double(&corespondingarray)[200], int& variablescount, Output* pOut, int writecount) {
	
	int left, right;
	left = ValueOrVariable(LHS);
	right = ValueOrVariable(RHS);

	int valueOfLeft, valueOfRight;

	if (left == VARIABLE_OP && right == VARIABLE_OP) {
		for (int i = 0; i < variablescount; i++) {
			if (allvariables[i] == LHS) {
				valueOfLeft = corespondingarray[i];
				break;
			}
		}

		for (int i = 0; i < variablescount; i++) {
			if (allvariables[i] == RHS) {
				valueOfRight = corespondingarray[i];
				break;
			}
		}

	}
	else if (left == VALUE_OP && right == VARIABLE_OP) {
		valueOfLeft = stod(LHS);
		for (int i = 0; i < variablescount; i++) {
			if (allvariables[i] == RHS) {
				valueOfRight = corespondingarray[i];
				break;
			}
		}
	}
	else if (left == VARIABLE_OP && right == VALUE_OP) {
		for (int i = 0; i < variablescount; i++) {
			if (allvariables[i] == LHS) {
				valueOfLeft = corespondingarray[i];
				break;
			}
		}
		valueOfRight = stod(RHS);
	}

	if (CompOperator == "==") {
		if (valueOfLeft == valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (CompOperator == "!=") {
		if (valueOfLeft != valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (CompOperator == "<") {
		if (valueOfLeft < valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (CompOperator == ">") {
		if (valueOfLeft > valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (CompOperator == ">=") {
		if (valueOfLeft >= valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (CompOperator == "<=") {
		if (valueOfLeft <= valueOfRight) {
			return true;
		}
		else {
			return false;
		}
	}
}

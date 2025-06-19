
#pragma once

// this file contains the functions that don't logically belong to any class
// and can be used by any class
// they are, in general, helper functions

#include <string>
#include "GUI/UI_Info.h"
#include "GUI/Input.h"
using namespace std;

enum OpType
{
	VALUE_OP,
	VARIABLE_OP,
	INVALID_OP
};

float GetSlopes(Point start, Point end, float& slope);
bool IsValue(string input);
bool IsVariable(string input);
OpType ValueOrVariable(string input);
//save
bool IsFileName(string input);


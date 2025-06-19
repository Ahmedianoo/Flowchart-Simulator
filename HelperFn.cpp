#include "HelperFn.h"
#include "GUI/UI_Info.h"
#include "GUI/Input.h"
#include <iostream>
using namespace std;

float GetSlopes(Point start, Point end, float& slope)
{
	Point eq;
	eq.x = end.x - start.x;
	eq.y = end.y - start.y;
	slope = float(eq.y) / float(eq.x);
	if (slope > 3.0)
	{
		slope = 3.0;
	}
	else if (slope < -3.0)
	{
		slope = -3.0;
	}

	float slopenormal = -1 / slope;

	if (slopenormal > 3)
	{
		slopenormal = 3.0;
	}
	else
	{
		if (slopenormal < -3)
		{
			slopenormal = -3.0;
		}
	}

	if (slope == 0.0)
	{
		slopenormal = -1 * slopenormal;
	}
	return slopenormal;
}


bool IsValue(string input)
{
	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.

	//TODO: complete this function

	int length = 0;
	int numberofdots = 0;
	int numberofnega = 0;
	int numberofdidgts = 0;
	while (input[length] != NULL)
	{
		length++;
	}
	if (input[0] == '-')
	{
		if (input[1] == '.')
		{
			return false;
		}
	}
	else
	{
		if (input[0] == '.')
		{
			return false;
		}
	}
	for (int i = 0; i < length; i++)
	{
		if (input[i] == '.')
		{
			numberofdots++;
		}
		if (input[i] == '-')
		{
			numberofnega++;
		}
		if (input[i] >= 48 && input[i] <= 57)
		{
			numberofdidgts++;
		}
	}
	if (numberofdidgts == 0)
	{
		return false;
	}
	if (numberofdots > 1)
	{
		return false;
	}
	if (numberofnega > 1)
	{
		return false;
	}
	for (int i = 0; i < length; i++)
	{
		if ((input[i] >= 48 && input[i] <= 57) == false)
		{
			if ((input[i] == '.') == false)
			{
				if ((input[i] == '-' && i == 0) == false)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	//TODO: complete this function
	int length = 0;
	while (input[length] != NULL)
	{
		length++;
	}

	if ((input[0] >= 65 && input[0] <= 90) == false)
	{
		if ((input[0] >= 97 && input[0] <= 122) == false)
		{
			if (input[0] != '_')
			{
				return false;
			}
		}
	}

	for (int i = 1; i < length; i++)
	{
		if ((input[i] >= 65 && input[i] <= 90) == false)
		{
			if ((input[i] >= 97 && input[i] <= 122) == false)
			{
				if ((input[i] >= 48 && input[i] <= 57) == false)
				{
					if (input[i] != '_')
					{
						return false;
					}
				}

			}
		}
	}

	return true;
}

OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function
	if (IsValue(input) == true)
	{
		return VALUE_OP;
	}
	else if (IsVariable(input) == true)
	{
		return VARIABLE_OP;
	}
	else
	{
		return INVALID_OP;
	}
}
//save// "/" ":" "\" "|" "<" ">" "?" "*" """
bool IsFileName(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == 47 || input[i] == 58 || input[i] == 92 || input[i] == 124 || input[i] == 60 || input[i] == 62 || input[i] == 63 || input[i] == 42 || input[i] == 34) {
			return false;
		}
	}
	return true;
}
#pragma once
#include "..\GUI\UI_Info.h"
class ForbiddenReigon
{
	
protected:
	Point pf1;
	Point pf2;
	Point pf3;
	Point pf4;

public:

	bool Isforbidden(Point P) const;

	// . = P
							//.
	//		pf1	____________________________ pf2
	//			|						 |
	//			|	___________________  |
	//			|	|				  |	 |
	//		.	|	|			.	  |	 |	.
	//			|	|		statement |	 |
	//			|	|				  |	 |
	//			|	-------------------	 |
	//			|		forbidden extra	 |
	//			|						 |
	//		pf4	-------------------------- pf3
							//.
	
	ForbiddenReigon();


};

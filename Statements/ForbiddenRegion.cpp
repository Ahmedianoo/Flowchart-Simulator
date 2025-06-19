#include "ForbiddenRegion.h"

bool ForbiddenReigon::Isforbidden(Point P) const
{
	if (
		(P.x >= pf2.x) && (P.x <= pf1.x) && (P.y <= pf4.y) && (P.y >= pf1.y)
		)
	{
		return true;
	}
	else return false;
}

ForbiddenReigon::ForbiddenReigon()
{}
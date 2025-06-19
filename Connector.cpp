#include "Connector.h"

Connector::Connector(Statement* Src, Statement* Dst, int x)
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	checker = x;
	setSrcStat(Src);
	setDstStat(Dst);
	Start = SrcStat->getOutlet(x);
	End = DstStat->getInlet();
	Selected = false;
}

void Connector::setSrcStat(Statement* Src)
{
	SrcStat = Src;
}

Statement* Connector::getSrcStat()
{
	return SrcStat;
}

void Connector::setDstStat(Statement* Dst)
{
	DstStat = Dst;
}

Statement* Connector::getDstStat()
{
	return DstStat;
}

void Connector::setStartPoint(Point P)
{
	Start = P;
}

Point Connector::getStartPoint()
{
	return Start;
}

void Connector::setEndPoint(Point P)
{
	End = P;
}

Point Connector::getEndPoint()
{
	return End;
}

void Connector::Draw(Output* pOut) const
{
	pOut->DrawConnector(Start, End, checker, Selected);
	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
}

int Connector::GetChecker() const
{
	return checker;
}

void Connector::SetSelected(bool truth)
{
	Selected = truth;
}

bool Connector::GetSelected()
{
	return Selected;
}

void Connector::setID(int id)
{
	ID = id;
}

int Connector::GetID() const
{
	return ID;
}

bool Connector::Is_In_Region(Point P) const
{
	//			End
	//	pxn	------------pxp
	//		 \		  /
	//		  \		P/
	//		   \  . /
	//			\  /
	//			 \/
	//			end


	if (End.x + 6 >= P.x && End.x - 6 <= P.x)
	{
		Point pxn;
		pxn.x = End.x - 6; pxn.y = End.y - 6;
		Point pxp;
		pxp.x = End.x + 6; pxp.y = End.y - 6;

		float slope1 = float(pxn.y - P.y) / float(pxn.x - P.x);
		float slope2 = float(pxn.y - End.y) / float(pxn.x - End.x);
		float slope3 = float(pxp.y - P.y) / float(pxp.x - P.x);
		float slope4 = float(pxp.y - End.y) / float(pxp.x - End.x);
		if (
			(slope2 >= slope1) && (slope3 >= slope4)
			)
		{
			return true;
		}
	}


	switch (checker)
	{
	case 0: // Normal goes down then moves to end
	{
		if (Start.y <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 6; j++)
			{
				for (int i = Start.x - 1; i < Start.x + 1; i++)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}

			for (int j = Start.y + 4; j < Start.y + 6; j++)
			{
				for (int i = Start.x - 1; i < End.x + 1; i++)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}

			for (int j = Start.y + 4; j < End.y + 1; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{

				}
			}
		}

		else {
			if (Start.x >= End.x && Start.y > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 6; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y + 4; j < Start.y + 6; j++)
				{
					for (int i = Start.x - 1; i < End.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y + 4; j < End.y + UI.ASSGN_HI + 11; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y + UI.ASSGN_HI + 9; j < End.y + UI.ASSGN_HI + 11; j++)
				{
					for (int i = End.x - 1; i < End.x + UI.ASSGN_WDTH / 2 + 11; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y + UI.ASSGN_HI + 11; j > End.y - 10; j--)
				{
					for (int i = End.x + UI.ASSGN_WDTH / 2 + 9; i < End.x + UI.ASSGN_WDTH / 2 + 11; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x + UI.ASSGN_WDTH / 2 + 11; i > End.x - 1; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x + 1; i < End.x - 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}
			}
			else {
				if (Start.x < End.x && Start.y > End.y)
				{
					for (int j = Start.y - 1; j < Start.y + 6; j++)
					{
						for (int i = Start.x - 1; i < Start.x + 1; i++)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = Start.y + 4; j < Start.y + 6; j++)
					{
						for (int i = Start.x - 1; i < End.x + 1; i++)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = Start.y + 4; j < End.y + UI.ASSGN_HI + 11; j++)
					{
						for (int i = End.x - 1; i < End.x + 1; i++)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = End.y + UI.ASSGN_HI + 9; j < End.y + UI.ASSGN_HI + 11; j++)
					{
						for (int i = End.x + 1; i > End.x - UI.ASSGN_WDTH / 2 - 11; i--)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = End.y + UI.ASSGN_HI + 11; j > End.y - 10; j--)
					{
						for (int i = End.x - UI.ASSGN_WDTH / 2 - 9; i > End.x - UI.ASSGN_WDTH / 2 - 11; i--)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = End.y - 9; j > End.y - 11; j--)
					{
						for (int i = End.x - UI.ASSGN_WDTH / 2 - 11; i > End.x + 1; i--)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}

					for (int j = End.y - 11; j < End.y + 1; j++)
					{
						for (int i = End.x + 1; i < End.x - 1; i++)
						{
							if (P.x == i && P.y == j)
								return true;
						}
					}
				}
			}
		}
		break;

	}
	case 1: // Right of the Condtional
	{
		if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 1; j++)
			{
				for (int i = Start.x - 1; i < End.x + 1; i++)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}
			for (int j = Start.y - 1; j < End.y; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}
		}
		else
		{
			if (Start.x >= End.x && Start.y + UI.ASSGN_HI / 2 > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y - 1; j > End.y - 11; j--)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = Start.x + 4; i < End.x; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}
			}

			if (Start.x >= End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y - 1; j < End.y - 11; j++)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x - 1; i > Start.x + 6; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i > End.x + 1; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}
			}
		}
	}
	case 2: // Left of the Condtional
	{

		if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 1; j++)
			{
				for (int i = Start.x + 1; i > End.x - 1; i--)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}
			for (int j = Start.y - 1; j < End.y; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{
					if (P.x == i && P.y == j)
						return true;
				}
			}
		}
		else
		{
			if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x + 1; i > Start.x - 6; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y - 1; j > End.y - 11; j--)
				{
					for (int i = Start.x - 4; i < Start.x - 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = Start.x - 4; i > End.x - 1; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}
			}

			if (Start.x <= End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x + 1; i > Start.x - 6; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = Start.y - 1; j < End.y - 11; j++)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x + 1; i > Start.x - 4; i--)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						if (P.x == i && P.y == j)
							return true;
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
	return false;
}

bool Connector::Is_In_Region(Statement* S) const
{
	Point P;
	switch (checker)
	{
	case 0: // Normal goes down then moves to end
	{
		if (Start.y <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 6; j++)
			{
				for (int i = Start.x - 1; i < Start.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}

				}
			}

			for (int j = Start.y + 4; j < Start.y + 6; j++)
			{
				for (int i = Start.x - 1; i < End.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}

			for (int j = Start.y + 4; j < End.y + 1; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}
		}

		else {
			if (Start.x >= End.x && Start.y > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 6; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y + 4; j < Start.y + 6; j++)
				{
					for (int i = Start.x - 1; i < End.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y + 4; j < End.y + UI.ASSGN_HI + 11; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y + UI.ASSGN_HI + 9; j < End.y + UI.ASSGN_HI + 11; j++)
				{
					for (int i = End.x - 1; i < End.x + UI.ASSGN_WDTH / 2 + 11; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y + UI.ASSGN_HI + 11; j > End.y - 10; j--)
				{
					for (int i = End.x + UI.ASSGN_WDTH / 2 + 9; i < End.x + UI.ASSGN_WDTH / 2 + 11; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x + UI.ASSGN_WDTH / 2 + 11; i > End.x - 1; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x + 1; i < End.x - 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}
			}
			else {
				if (Start.x < End.x && Start.y > End.y)
				{
					for (int j = Start.y - 1; j < Start.y + 6; j++)
					{
						for (int i = Start.x - 1; i < Start.x + 1; i++)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = Start.y + 4; j < Start.y + 6; j++)
					{
						for (int i = Start.x - 1; i < End.x + 1; i++)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = Start.y + 4; j < End.y + UI.ASSGN_HI + 11; j++)
					{
						for (int i = End.x - 1; i < End.x + 1; i++)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = End.y + UI.ASSGN_HI + 9; j < End.y + UI.ASSGN_HI + 11; j++)
					{
						for (int i = End.x + 1; i > End.x - UI.ASSGN_WDTH / 2 - 11; i--)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = End.y + UI.ASSGN_HI + 11; j > End.y - 10; j--)
					{
						for (int i = End.x - UI.ASSGN_WDTH / 2 - 9; i > End.x - UI.ASSGN_WDTH / 2 - 11; i--)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = End.y - 9; j > End.y - 11; j--)
					{
						for (int i = End.x - UI.ASSGN_WDTH / 2 - 11; i > End.x + 1; i--)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}

					for (int j = End.y - 11; j < End.y + 1; j++)
					{
						for (int i = End.x + 1; i < End.x - 1; i++)
						{
							P.x = i;
							P.y = j;
							if (S->Is_In_Region(P) == true)
							{
								return true;
							}
						}
					}
				}
			}
		}
		break;

	}
	case 1: // Right of the Condtional
	{
		if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 1; j++)
			{
				for (int i = Start.x - 1; i < End.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}
			for (int j = Start.y - 1; j < End.y; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}
		}
		else
		{
			if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y - 1; j > End.y - 11; j--)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = Start.x + 4; i < End.x; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}
			}

			if (Start.x >= End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x - 1; i < Start.x + 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y - 1; j < End.y - 11; j++)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x - 1; i > Start.x + 6; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i > End.x + 1; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}
			}
		}
	}
	case 2: // Left of the Condtional
	{

		if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
		{
			for (int j = Start.y - 1; j < Start.y + 1; j++)
			{
				for (int i = Start.x + 1; i > End.x - 1; i--)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}
			for (int j = Start.y - 1; j < End.y; j++)
			{
				for (int i = End.x - 1; i < End.x + 1; i++)
				{
					P.x = i;
					P.y = j;
					if (S->Is_In_Region(P) == true)
					{
						return true;
					}
				}
			}
		}
		else
		{
			if (Start.x < End.x && Start.y + UI.ASSGN_HI / 2 > End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x + 1; i > Start.x - 6; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y - 1; j > End.y - 11; j--)
				{
					for (int i = Start.x - 4; i < Start.x - 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = Start.x - 4; i > End.x - 1; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}
			}

			if (Start.x <= End.x && Start.y + UI.ASSGN_HI / 2 <= End.y)
			{
				for (int j = Start.y - 1; j < Start.y + 1; j++)
				{
					for (int i = Start.x + 1; i > Start.x - 6; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = Start.y - 1; j < End.y - 11; j++)
				{
					for (int i = Start.x + 4; i < Start.x + 6; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 9; j > End.y - 11; j--)
				{
					for (int i = End.x + 1; i > Start.x - 4; i--)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}

				for (int j = End.y - 11; j < End.y + 1; j++)
				{
					for (int i = End.x - 1; i < End.x + 1; i++)
					{
						P.x = i;
						P.y = j;
						if (S->Is_In_Region(P) == true)
						{
							return true;
						}
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
	return false;
}

void Connector::Save(ofstream& OutFile) {
	if (checker == 0) {
		OutFile << SrcStat->GetID() << " " << DstStat->GetID() << " " << "0";
	}
	else if (checker == 1) {
		OutFile << SrcStat->GetID() << " " << DstStat->GetID() << " " << "1";
	}
	else if (checker == 2) {
		OutFile << SrcStat->GetID() << " " << DstStat->GetID() << " " << "2";
	}
}

Connector::~Connector()
{
	SrcStat = NULL;
	DstStat = NULL;
}

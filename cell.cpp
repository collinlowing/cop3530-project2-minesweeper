#include "cell.hpp"

Cell::Cell(bool mine)
{
	this->mine = mine;
	flagged = false;
	clicked = false;
	numAdjMines = 0;
}

bool Cell::IsMine()
{
	return mine;
}

void Cell::setAdjMines(int numAdjMines)
{
	this->numAdjMines = numAdjMines;
}

bool Cell::Click()
{
	if (clicked)
		return false;
	if (flagged)
		return false;
	else
	{
		clicked = true;
		return true;
	}
}

void Cell::ToggleFlag()
{
	if (!flagged)
		flagged = true;
	else
		flagged = false;
}

std::ostream& operator<<(std::ostream& os, const Cell& c)
{
	if (c.flagged)
		os << Cell::FLAG;
	if (c.clicked && !c.mine)
	{
		if (c.numAdjMines == 0)
			os << Cell::NO_ADJACENT_MINES;
		else
			os << c.numAdjMines;
	}
	if (c.mine)
	{
		os << Cell::MINE;
	}
	else
		os << " ";

	return os;
}
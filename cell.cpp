#include "cell.hpp"

const std::string Cell::MINE = "*";
const std::string Cell::FLAG = "F";
const std::string Cell::NO_ADJACENT_MINES = "0";
const int Cell::ASCII_ZERO = 48;

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

bool Cell::IsFlag()
{
	return flagged;
}

void Cell::SetAdjacentMineCount(int numAdjMines)
{
	this->numAdjMines = numAdjMines;
}

int Cell::GetAdjacentMineCount()
{
	return numAdjMines;
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
	else if (c.clicked && !c.mine)
	{
		if (c.numAdjMines == 0)
			os << Cell::NO_ADJACENT_MINES;
		else
			os << c.numAdjMines;
	}
	else if (c.clicked && c.mine)
	{
		os << Cell::MINE;
	}
	else
		os << " ";

	return os;
}
#include "minefield.hpp"

Minefield::Minefield()
{

}

Minefield::Minefield(std::string file)
{
    this->fileName = file;
}

Minefield::~Minefield()
{
    for(int i = 0; i < x; i++)
    {
        delete [] cell[i];
    }
    delete [] cell;
}

void Minefield::ReadFile(int x, int y)
{
	rows = x;
	columns = y;
	std::string row;
	int foundMine;
	cell = new Cell*[rows];
	for (int i = 0; i < rows; i++)
	{
		cell[i] = new Cell[columns];
	}

	std::ifstream inputFile;
	inputFile.open(fileName);

	while (getline(inputFile, row))
	{
		row.find('*', foundMine+1);
		if (foundMine != string::npos)
		{
			// assign mine
		}
	}
	

	inputFile.close();
}

bool Minefield::Click(int x, int y)
{
	if (cell[x][y].IsFlag())
		return false;
	else
		Expand(x, y);
		return true;
}

bool Minefield::Flag(int x, int y)
{
	if (!cell[x][y].isCleared())
		cell[x][y].ToggleFlag();
		return true;
	else
		return false;
}

// Implement completely.
void Minefield::Expand(int x, int y)
{
	int adjmc = Cell[x][y]getAdjacentMineCount()
	if (cell[x][y].isMine() || adjmc > 0)
	{
		if (!cell[x][y].isCleared())
		{
			cell[x][y].Clear();
		}
		return;
	}
	for(int i = x - 1; i <= x + 1; i++)
	{
		if (i < 0)
			continue;
		else if (i >= x)
			break;
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j < 0)
				continue;
			else if (j >= y)
				break;
			if (adjmc == 0)
			{
				cell[x][y].SetAdjacentMineCount(9);
				Expand(i, j);
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Minefield& mf)
{

    return os;
}
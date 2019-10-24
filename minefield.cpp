#include "minefield.hpp"

Minefield::Minefield()
{
	rows = 0;
	columns = 0;
}

Minefield::~Minefield()
{
    for(int i = 0; i < rows; i++)
    {
        delete [] cell[i];
    }
    delete [] cell;
}

void Minefield::ReadFile(std::string file, int x, int y)
{
	rows = x;
	columns = y;
	
	std::string row;
	size_t foundMine;
	cell = new Cell*[rows];
	int i = 0;

	for(int i = 0; i < rows; i++)
	{
		cell[i] = new Cell[columns];
	}
	

	std::ifstream inputFile;
	inputFile.open(file);

	while (!inputFile.eof())
	{
		getline(inputFile, row);
		while(foundMine != std::string::npos)
		{
			foundMine = row.find('*');
		
			// Assign mine for coordinates on the board
			cell[i][foundMine] = Cell(true);
		}
		i++;
	}

	inputFile.close();
}

bool Minefield::Click(int x, int y)
{
	if (cell[x][y].IsFlag())
		return false;
	else
	{
		Expand(x, y);
		return true;
	}
}

bool Minefield::Flag(int x, int y)
{
	if (!cell[x][y].IsCleared())
	{
		cell[x][y].ToggleFlag();
		return true;
	}
	else
		return false;
}


void Minefield::Expand(int x, int y)
{
	int adjmc = cell[x][y].GetAdjacentMineCount();
	if (cell[x][y].IsMine() || adjmc > 0)
	{
		if (!cell[x][y].IsCleared())
		{
			cell[x][y].Click();
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
	os << "      ";
	for(int i = 0; i < mf.columns - 1; i++)
	{
		os << i << "   ";
	}
	os << (mf.columns - 1) << " \n";

	os << "    ";
	for(int j = 0; j < mf.columns; j++)
	{
		os <<"+---";
	}
	os << "+\n";

	for(int i = 0; i < mf.rows; i++)
	{
		os << "  " << i;
		for(int j = 0; j < mf.columns; j++)
		{
			os << " | " << mf.cell[i][j];
		}
		os << " |\n";

		os << "    ";
		for(int j = 0; j < mf.columns; j++)
		{
			os << "+---";
		}
		os << "+\n";
	}
	
    return os;
}
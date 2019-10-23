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
    for(int i = 0; i < rows; i++)
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
	size_t foundMine;
	cell = new Cell*[rows];
	int i = 0;

	for(int i = 0; i < rows; i++)
	{
		cell[i] = new Cell[columns];
	}
	

	std::ifstream inputFile;
	inputFile.open(fileName);

	while (getline(inputFile, row))
	{
		while(foundMine != std::string::npos)
		{
			row.find('*', foundMine+1);
		
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
	for(int i = 0; i < Minefield::columns - 2; i++)
	{
		os << i << "   ";
	}
	os << Minefield::columns - 1 << " \n";

	os << "    ";
	for(int j = 0; j < Minefield::columns - 1; j++)
	{
		os <<"+---+";
	}
	os << "\n";
	for(int i = 0; i < Minefield::rows - 1; i++)
	{
		//os << "  " << j FIXME
		for(int j = 0; j < Minefield::columns - 1; j++)
		{
			os << " | " << Minefield::cell[i][j] << " |";
			os <<"+---+";
		}
		os << "\n";
	}
	

	"      0   1   2   3 \n"
	"    +---+---+---+---+\n"
	"  0 |   |   |   |   |\n"
	"    +---+---+---+---+\n"
	"  1 |   |   |   |   |\n"
	"    +---+---+---+---+\n"
	"  2 |   |   |   |   |\n"
	"    +---+---+---+---+\n"
	"  3 |   |   |   |   |\n"
	"    +---+---+---+---+\n";
    return os;
}
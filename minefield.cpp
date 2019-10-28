#include "minefield.hpp"

Minefield::Minefield()
{
	numMines = 0;
	minesFlagged = 0;
	rows = 0;
	columns = 0;
	hitMine = false;
}

/* Causes abort signal. Professor Coffey and I could not figure it out.
Minefield::~Minefield()
{
    for(int i = 0; i < rows; i++)
    {
        delete [] cell[i];
    }
    delete [] cell;
}
*/

void Minefield::ReadFile(std::string file, int x, int y)
{
	rows = x;
	columns = y;
	
	std::string row;
	size_t foundMine;
	cell = new Cell*[rows];
	//Cell * temp;

	for(int i = 0; i < rows; i++)
	{
		cell[i] = new Cell[columns];
	}
	

	std::ifstream inputFile;
	inputFile.open(file);

	int i = 0;
	while (!inputFile.eof())
	{
		getline(inputFile, row);
		while(foundMine != std::string::npos)
		{
			foundMine = row.find('*');
			numMines++;
		
			//temp = cell[i][foundMine];
			cell[i][foundMine].SetMine(true); //this is causing errors

			//delete temp;
		}
		i++;
	}

	inputFile.close();
}

bool Minefield::Click(int x, int y)
{
	if (cell[x][y].IsFlag() || cell[x][y].IsCleared())
		return false;
	else if (!cell[x][y].IsMine())
	{
		Expand(x, y);
		return true;
	}
	else
	{
		hitMine = true;
		return true;
	}
}

bool Minefield::Flag(int x, int y)
{
	if (cell[x][y].IsMine() && !cell[x][y].IsFlag())
		minesFlagged++;
	
	if (!cell[x][y].IsCleared())
	{
		cell[x][y].ToggleFlag();
		if (minesFlagged == numMines)
		{
			gameWon = true;
		}
		return true;
	}
	else
		return false;
}

bool WonGame()
{
	return gameWon;
}

bool LoseGame()
{
	return hitMine;	
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

std::string Minefield::GameOver()
{
	std::ostringstream os;
	
	os << "      ";
	for (int i = 0; i < columns - 1; i++)
	{
		os << i << "   ";
	}
	os << (columns - 1) << " \n";

	os << "    ";
	for (int j = 0; j < columns; j++)
	{
		os << "+---";
	}
	os << "+\n";

	for (int i = 0; i < rows; i++)
	{
		os << "  " << i;
		for (int j = 0; j < columns; j++)
		{
			if (cell[i][j].IsMine())
				os << " | " << "*";
			else
				os << " | " << " ";
		}
		os << " |\n";

		os << "    ";
		for (int j = 0; j < columns; j++)
		{
			os << "+---";
		}
		os << "+\n";
	}

	return os.str();
}

std::ostream& operator<<(std::ostream& os, const Minefield& mf)
{
	std::cout << "***" << mf.rows << std::endl;
	std::cout << "***" << mf.columns << std::endl;
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
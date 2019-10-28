#include "ui.hpp"

UI::UI()
{
    gameOver = false;
    x = -1;
    y = -1;
    cmd = 'x';
	prompt = "Please enter a file name with the minefield information: ";
}

bool UI::IsGameOver()
{
	std::ostringstream os;
	os << board;
	if (gameOver)
	{
		prompt = os.str() + "Game Over!";
	}
	else
	{
		prompt = os.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
	}
    return gameOver;
}

std::string UI::GetPrompt()
{
	return prompt;
    std::ostringstream os;
	if (gameOver)
	{
		return board.GameOver() + "Game Over!";
	}
}

bool UI::SetFileName(std::string fileName)
{
    int x;
    int y;
    std::string line;

	std::ostringstream os;

    std::ifstream inputFile;
    inputFile.open(fileName);

	if (!inputFile.is_open())
	{
		prompt = "Please enter a file name with the minefield information: ";
		return false;
	} 
    else
    {
        while (getline(inputFile, line))
            y++;

        x = line.length();

        board.ReadFile(fileName, x, y);
        inputFile.close();

		os << board;
		prompt = os.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";

        return true;
    }
}

bool UI::Move(char cmd, int x, int y)
{
	std::ostringstream os;

    switch(cmd)
    {
        case 'c':
        case 'C':
			if (board.Click(x, y))
			{
				os << board;
				prompt = os.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
				if (board.LoseGame())
				{
					prompt = board.GameOver() + "Game Over!";
					gameOver = true;
				}
				return true;
			}
            else
            {
				prompt = "Invalid move. Please enter your next move: ";
                return false;
            }
            break;
        case 'f':
        case 'F':
			if (board.Flag(x, y))
			{
				os << board;
				prompt = os.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
				if (board.WonGame())
				{
					prompt = board.GameOver() + "Game Won!";
					gameOver = true;
				}
				return true;
			}
            else
            {
				prompt = "Invalid move. Please enter your next move: ";
                return false;
            }
            break;
        default:
            prompt = "Invalid move. Please enter your next move: ";
            return false;
    }
}

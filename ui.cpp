#include "ui.hpp"

UI::UI()
{
    gameOver = false;
    x = -1;
    y = -1;
    cmd = 'x';
}

bool UI::IsGameOver()
{
    return gameOver;
}

std::string UI::GetPrompt()
{
    std::ostringstream os;
    if(gameOver)
        return "Game Over!"; //add call to minefield to print cleared mine
    else if(!SetFileName(fileName))
    {
        return "Please enter a file name with the minefield information: ";
    }
    else if(!Move(cmd, x, y))
    {
        return "Invalid move. Please enter your next move: ";
    }
    else
    {
        os << board;
        return os.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
    }
    
}

bool UI::SetFileName(std::string fileName)
{
    int x;
    int y;
    std::string line;

    std::ifstream inputFile;
    inputFile.open(fileName);

    if(!inputFile.is_open())
        return false;
    else
    {
        while (getline(inputFile, line))
            y++;

        x = line.length();

        board.ReadFile(fileName, x, y);
        inputFile.close();
        return true;
    }
}

bool UI::Move(char cmd, int x, int y)
{
    switch(cmd)
    {
        case 'c':
        case 'C':
            if(board.Click(x, y))
                return true;
            else
            {
                std::cout << "ERROR: cell cannot be clicked." << std::endl;
                return false;
            }
            break;
        case 'f':
        case 'F':
            if(board.Flag(x, y))
                return true;
            else
            {
                std::cout << "ERROR: cell cannot be flagged." << std::endl;
                return false;
            }
            break;
        default:
            std::cout << "ERROR: Not a valid command." << std::endl;
            return false;
    }
}

std::ostream& operator<<(std::ostream& os, const UI& ui)
{

    return os;
}
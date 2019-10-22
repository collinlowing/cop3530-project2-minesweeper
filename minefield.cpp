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
        delete [] cells[i];
    }
    delete [] cells;
}

void Minefield::ReadFile(std::string fileName)
{
    
}

bool Click(int x, int y)
{

}

bool Flag(int x, int y)
{

}

std::ostream& operator<<(std::ostream& os, const Minefield& mf)
{

    return os;
}
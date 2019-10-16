#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include "cell.hpp"
#include <iostream>
#include <string>
#include <sstream>

class Minefield
{
    private:
		int row;
		int col;
		std::string fileName;
		Cell ** cells;
    public:
		Minefield(std::string fileName);
		void ReadFile();
		
};

#endif
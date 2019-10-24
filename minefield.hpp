#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include "cell.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Minefield
{
    private:
		int rows;
		int columns;
		Cell ** cell;
    public:
		Minefield();
		Minefield(std::string file);
		~Minefield();
		void ReadFile(std::string file, int x, int y);
		bool Click(int x, int y);
		void Expand(int x, int y);
		bool Flag(int x, int y);
		friend std::ostream& operator<<(std::ostream& os, const Minefield& mf);
};

#endif
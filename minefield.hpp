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
		int x;
		int y;
		std::string fileName;
		Cell ** cells;
    public:
		Minefield();
		Minefield(std::string file);
		~Minefield();
		void ReadFile(std::string fileName);
		bool Click(int x, int y);
		bool Flag(int x, int y);
		friend std::ostream& operator<<(std::ostream& os, const Minefield& mf);
};

#endif
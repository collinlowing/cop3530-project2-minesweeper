#ifndef CEL_HPP
#define CEL_HPP

#include<iostream>
#include<sstream>
#include<iomanip>

class Cell
{
    private:
		bool mine;
		bool flagged;
		bool clicked;
		int numAdjMines;
    public:
		Cell(bool mine);
		bool IsMine();
		bool Click();
		void ToggleFlag();
		void setAdjMines(int numAdjMines);
		enum status { MINE, FLAG, NO_ADJACENT_MINES };
		friend std::ostream& operator<<(std::ostream& os, const Cell& c);
};

#endif
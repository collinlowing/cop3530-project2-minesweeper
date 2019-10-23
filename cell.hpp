#ifndef CEL_HPP
#define CEL_HPP

#include<iostream>
#include<sstream>
#include<string>
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
		bool IsFlag();
		bool Click();
		void ToggleFlag();
		void SetAdjacentMineCount(int numAdjMines);
		int GetAdjacentMineCount();
		static const std::string MINE;
		static const std::string FLAG;
		static const std::string NO_ADJACENT_MINES;
		static const int ASCII_ZERO;
		friend std::ostream& operator<<(std::ostream& os, const Cell& c);
};

#endif
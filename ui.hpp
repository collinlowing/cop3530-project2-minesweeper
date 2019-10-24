#ifndef UI_HPP
#define UI_HPP

#include "minefield.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

class UI
{
    private:
		bool gameOver;
		std::string prompt;
		std::string fileName;
		Minefield board;
		char cmd;
		int x;
		int y;
    public:
		UI();
		bool IsGameOver();
		std::string GetPrompt();
		bool SetFileName(std::string fileName);
		bool Move(char cmd, int x, int y);
		friend std::ostream& operator<<(std::ostream& os, const UI& ui);
};

#endif
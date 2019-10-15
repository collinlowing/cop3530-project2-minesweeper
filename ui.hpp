#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <string>
#include <sstream>

class UI
{
    private:

    public:
    bool IsGameOver();
    std::string GetPrompt();
    bool SetFileName(std::string);
    bool Move(char cmd, int x, int y);
};

#endif
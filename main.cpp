#include "cell.hpp"
#include "minefield.hpp"
#include "ui.hpp"

int main()
{
	UI ui;
	std::string commandLine;
	std::string substring;
	char command;
	char ch;
	int stringSize;
	std::string[2] coor;
	int x;
	int y;
	size_t pos1 = 0;
	size_t pos2;

	while (!ui.IsGameOver())
	{
		std::cout << ui.GetPrompt() << endl;

		std::cin >> commandLine;
		stringSize = commandLine.length;

		pos2 = commandLine.find(' ');
		substring = commandLine.substr(pos1, pos2);
		pos1 = pos2 + 1;
		commandLine = commandLine.substr(pos1, stringSize);
		if (substring.length != 1)
		{
			std::cout << "Invalid command, try again." << endl;
			continue;
		}


		pos2 = commandLine.find(' ');
		coor[0] = commandLine.substr(pos1, pos2);
		pos1 = pos2 + 1;
		commandLine = commandLine.substr(pos1, stringSize);
		if (coor[0].length != 1)
		{
			std::cout << "Invalid command, try again." << endl;
			continue;
		}

		pos2 = commandLine.find(' ');
		coor[1] = commandLine.substr(pos1, pos2);
		if (coor[1].length != 1)
		{
			std::cout << "Invalid command, try again." << endl;
			continue;
		}

		command = substring[0];
		
		ch = coor[0][0];
		x = ch - '0';

		ch = coor[1][0];
		y = ch - '0';

		ui.Move(command, x, y);
	}
	return 0;
}
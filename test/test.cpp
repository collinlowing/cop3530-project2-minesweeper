#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>
#include "catch/catch.hpp"
#include "../cell.hpp"
#include "../ui.hpp"
#include "../minefield.hpp"

// Setting some "expected" output strings to use in tests that follow

const std::string NOTHING_CLICKED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  1 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  2 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  3 |   |   |   |   |\n"
"    +---+---+---+---+\n";

const std::string TOP_LEFT_CLICKED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 | "+Cell::NO_ADJACENT_MINES+" | "+Cell::NO_ADJACENT_MINES+" | 1 |   |\n"
"    +---+---+---+---+\n"
"  1 | 1 | 1 | 2 |   |\n"
"    +---+---+---+---+\n"
"  2 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  3 |   |   |   |   |\n"
"    +---+---+---+---+\n";

const std::string BOTTOM_RIGHT_NUMBER_CLICKED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 | "+Cell::NO_ADJACENT_MINES+" | "+Cell::NO_ADJACENT_MINES+" | 1 |   |\n"
"    +---+---+---+---+\n"
"  1 | 1 | 1 | 2 |   |\n"
"    +---+---+---+---+\n"
"  2 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  3 |   |   | 3 |   |\n"
"    +---+---+---+---+\n";

const std::string TOP_ROW_ALL_CLICKED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 | "+Cell::NO_ADJACENT_MINES+" | "+Cell::NO_ADJACENT_MINES+" | 1 | 1 |\n"
"    +---+---+---+---+\n"
"  1 | 1 | 1 | 2 |   |\n"
"    +---+---+---+---+\n"
"  2 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  3 |   |   | 3 |   |\n"
"    +---+---+---+---+\n";

const std::string FLAG_ADDED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 | "+Cell::NO_ADJACENT_MINES+" | "+Cell::NO_ADJACENT_MINES+" | 1 | 1 |\n"
"    +---+---+---+---+\n"
"  1 | 1 | 1 | 2 | "+Cell::FLAG+" |\n"
"    +---+---+---+---+\n"
"  2 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  3 |   |   | 3 |   |\n"
"    +---+---+---+---+\n";

const std::string MINES_UNEARTHED =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 |   |   |   |   |\n"
"    +---+---+---+---+\n"
"  1 |   |   |   | * |\n"
"    +---+---+---+---+\n"
"  2 | * |   |   | * |\n"
"    +---+---+---+---+\n"
"  3 |   | * |   | * |\n"
"    +---+---+---+---+\n";

const std::string CLEARED_MINEFIELD =
"      0   1   2   3 \n"
"    +---+---+---+---+\n"
"  0 | "+Cell::NO_ADJACENT_MINES+" | "+Cell::NO_ADJACENT_MINES+" | 1 | 1 |\n"
"    +---+---+---+---+\n"
"  1 | 1 | 1 | 2 | "+Cell::FLAG+" |\n"
"    +---+---+---+---+\n"
"  2 |   | 2 | 4 |   |\n"
"    +---+---+---+---+\n"
"  3 | 2 |   | 3 |   |\n"
"    +---+---+---+---+\n";




TEST_CASE("Cell with mine")
{
	std::ostringstream os;
	bool mine = true;
	Cell c;
	c.SetMine(mine);

	REQUIRE(c.IsMine());

	os << c;
	REQUIRE(" " == os.str()); // cell has not been uncovered yet

	os.str(""); // reset stream to empty string
	c.ToggleFlag();
	os << c;
	REQUIRE(Cell::FLAG == os.str());

	bool clickSuccessful = c.Click();
	REQUIRE(!clickSuccessful); // cannot click a cell that has a flag on it

	os.str(""); // reset stream to empty string
	c.ToggleFlag();
	os << c;
	REQUIRE(" " == os.str()); // flag should be gone

	os.str(""); // reset stream to empty string
	c.Click();
	os << c;
	REQUIRE(Cell::MINE == os.str());
}

TEST_CASE("Cell without mine")
{
	bool mine = false;
	Cell c;
	c.SetMine(mine);
	REQUIRE(!c.IsMine());

	std::ostringstream os;
	os << c;
	REQUIRE(" " == os.str());

	os.str(""); // reset stream to empty string
	c.Click();
	os << c;
	REQUIRE(Cell::NO_ADJACENT_MINES == os.str());

	os.str(""); // reset stream to empty string
	c.SetAdjacentMineCount(6); // set arbitrary number of adjacent mines
	os << c;
	REQUIRE("6" == os.str());

	bool reClicked = c.Click();
	REQUIRE(!reClicked);
}


TEST_CASE("Minefield Initialization and display")
{
	std::ostringstream os;
	Minefield mf;

	mf.ReadFile("fourXfour.in", 4, 4);
	os << mf;

	REQUIRE(NOTHING_CLICKED == os.str());
}


TEST_CASE("Minefield Game Play")
{
	std::ostringstream os;
	Minefield mf;

	bool canClick;
	bool isFlagged;

	mf.ReadFile("fourXfour.in", 4, 4);

	canClick = mf.Click(-1,0);
	REQUIRE(!canClick);
	canClick = mf.Click(4,0);

	isFlagged = mf.Flag(4,0);
	REQUIRE(!isFlagged);
}

/*
TEST_CASE("UI class - Winner")
{
	// test get file name
	UI ui;
	std::string prompt;
	bool isValidInput;
	bool isValidMove = false;

	REQUIRE(!ui.IsGameOver());

	prompt = ui.GetPrompt();
	REQUIRE("Please enter a file name with the minefield information: " == prompt);
	// class would use cin, we'll hard-code an expected input

	isValidInput = ui.SetFileName("foo.bar.baz"); // file does not exist on our system
	REQUIRE(!isValidInput);

	prompt = ui.GetPrompt();
	REQUIRE("Please enter a file name with the minefield information: " == prompt);
	
	isValidInput = ui.SetFileName("fourXfour.in");
	REQUIRE(isValidInput);

	// should now be in game play mode
	prompt = ui.GetPrompt();
	REQUIRE(NOTHING_CLICKED+"Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: " == prompt);

	isValidMove = ui.Move('z', 0, 0); // not a click or a flag
	REQUIRE(!isValidMove);
	prompt = ui.GetPrompt();
	REQUIRE("Invalid move. Please enter your next move: " == prompt);

	isValidMove = ui.Move('C', -1, 0); // above the minefield
	REQUIRE(!isValidMove);

	isValidMove = ui.Move('c', 0, -1); // left of the minefield
	REQUIRE(!isValidMove);

	isValidMove = ui.Move('F', 4, 0); // below the minefield
	REQUIRE(!isValidMove);

	isValidMove = ui.Move('f', 0, 4); // right of the minefield
	REQUIRE(!isValidMove);

	ui.Move('c', 0, 0);
	prompt = ui.GetPrompt();
	REQUIRE(TOP_LEFT_CLICKED+"Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: " == prompt);

	ui.Move('C', 0, 3);
	ui.Move('c', 3, 2);
	ui.Move('f', 1, 3);
	prompt = ui.GetPrompt();
	REQUIRE(FLAG_ADDED+"Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: " == prompt);

	// click the rest of the cells without mines
	ui.Move('c', 3, 0);
	ui.Move('c', 3, 2);
	ui.Move('c', 2, 1);

	REQUIRE(!ui.IsGameOver());
	ui.Move('c', 2, 2);

	prompt = ui.GetPrompt();
	REQUIRE(CLEARED_MINEFIELD+"Game Over!" == prompt);

	REQUIRE(ui.IsGameOver());
}

TEST_CASE("UI class - Loser")
{
	UI ui;
	ui.SetFileName("fourXfour.in");

	ui.Move('c', 3, 3); // mine
	std::string prompt = ui.GetPrompt();
	REQUIRE(MINES_UNEARTHED+"Game Over!" == prompt);

	REQUIRE(ui.IsGameOver());
}
*/

// Compile & run:
// make clean test

#pragma once
#include <vector>
#include "enums.h"

class Field {
private:
	const int MINE = -1;

	int rowsNumber;
	int colsNumber;
	int minesNumber;

	std::vector<std::vector<int>> mines;
	std::vector<std::vector<bool>> opened;
	std::vector<std::vector<bool>> flags;


	void initializeMines();
	void initializeDigits();
	void incrementDigitsAround(int x, int y);

	Difficulty difficulty;
public:
	Field(int difficulty);
	int getRowsNumber();
	int getColsNumber();

	bool hasMineAt(int x, int y);
	int getDigitAt(int x, int y);

	void setFlag(int x, int y);
	bool hasFlagAt(int x, int y);

	void openCell(int x, int y);
	bool isCellOpened(int x, int y);
	int getFlagsAround(int x, int y);
	bool hasCell(int x, int y);

	void openAround(int x, int y);
	bool hasOpenedMines();
	GameStatus getGameStatus();
	Difficulty getDifficulty();
};
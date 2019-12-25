#pragma once
#include <vector>
#include <time.h>
#include <iostream>

#include "../../Config/enums.h"
#include "../../Config/constants.h"

class Field {
private:
	const int MINE = -1;

	int rowsNumber;
	int colsNumber;
	int minesNumber;

	std::vector<std::vector<int>> mines;
	std::vector<std::vector<bool>> opened;
	std::vector<std::vector<bool>> flags;

	
	
	void incrementDigitsAround(int x, int y);
public:
	Field(int rowsNumber, int colsNumber, int minesNumber);

	void eraseAll();
	void initializeDigits();
	void initializeMines(int x, int y);

	void setFieldConfiguration(int rowsNumber, int colsNumber, int minesNumber);
	int getRowsNumber();
	int getColsNumber();

	bool hasMineAt(int x, int y);
	int getDigitAt(int x, int y);

	int setFlag(int x, int y);
	bool hasFlagAt(int x, int y);

	void openCell(int x, int y);
	bool isCellOpened(int x, int y);
	int getFlagsAround(int x, int y);
	bool hasCell(int x, int y);

	void openAround(int x, int y);
	bool hasOpenedMines();

	bool hasFlags();
	bool hasOpenedCells();
	void generateWithSpaceAround(int x, int y);
	void openAllMines();
};
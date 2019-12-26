#pragma once

#include <vector>
#include <time.h>
#include <iostream>

#include "../../Config/enums.h"
#include "../../Config/constants.h"

class Field {
private:
	int rowsNumber;
	int colsNumber;
	int minesNumber;

	std::vector<std::vector<int>> mines;
	std::vector<std::vector<bool>> opened;
	std::vector<std::vector<bool>> flags;
	
	void incrementDigitsAround(int x, int y);
public:
	Field(int rowsNumber, int colsNumber, int minesNumber);

	void initializeDigits();
	void initializeMines(int x, int y);
	void setFieldConfiguration(int rowsNumber, int colsNumber, int minesNumber);
	void openCell(int x, int y);
	void generateWithSpaceAround(int x, int y);
	void openAllMines();
	void openAround(int x, int y);
	void toggleFlag(int x, int y);

	int getRowsNumber();
	int getColsNumber();
	int getDigitAt(int x, int y);
	int getFlagsAround(int x, int y);

	bool hasMineAt(int x, int y);
	bool hasFlagAt(int x, int y);
	bool isCellOpened(int x, int y);
	bool hasCell(int x, int y);
	bool hasOpenedMines();
	bool hasFlags();
	bool hasOpenedCells();
};
#include "Field.h"
#include <time.h>

Field::Field(int cols, int rows, int minesAmount)
{
	colsAmount = cols;
	rowsAmount = rows;
	minesNumber = minesAmount;

	opened.resize(rowsAmount);
	mines.resize(rowsAmount);
	flags.resize(rowsAmount);

	for (int i = 0; i < rowsAmount; i++) {
		opened[i].resize(colsAmount, false);
		mines[i].resize(colsAmount, 0);
		flags[i].resize(colsAmount, false);
	}


	initializeMines();
	initializeDigits();
	
	//int k = 0;

	/*for (int i = 0; i < rowsAmount; i++) {
		for (int j = 0; j < colsAmount; j++) {
			opened[i][j] = false;
		}
	}*/
}

int Field::getRowsAmount()
{
	return rowsAmount;
}

int Field::getColsAmount()
{
	return colsAmount;
}

bool Field::hasMineAt(int x, int y)
{
	return mines[x][y] == -1;
}

int Field::getDigitAt(int x, int y)
{
	return mines[x][y];
}

void Field::setFlag(int x, int y)
{
	flags[x][y] = !flags[x][y];
}

bool Field::hasFlagAt(int x, int y)
{
	return flags[x][y];
}

void Field::initializeMines()
{
	int minesLeft = minesNumber;

	srand(time(0));
	while (minesLeft) {
		int x = rand() % (colsAmount - 1);
		int y = rand() % (rowsAmount - 1);

		if (!mines[x][y]) {
			mines[x][y] = -1;
			minesLeft--;
		}
	}
}

void Field::initializeDigits()
{
	for (int i = 0; i < rowsAmount; i++) {
		for (int j = 0; j < colsAmount; j++) {
			if (mines[i][j] == -1) {
				incrementDigitsAround(i, j);
			}
		}
	}
}

void Field::incrementDigitsAround(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && i < rowsAmount && j >= 0 && j < colsAmount) {
				if (mines[i][j] != -1) {
					mines[i][j]++;
				}
			}
		}
	}
}

void Field::openCell(int x, int y)
{
	opened[x][y] = true;

	if (mines[x][y] == 0) {


		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				if (i >= 0 && i < rowsAmount && j >= 0 && j < colsAmount) {
					if (!hasFlagAt(i, j)) {
						if (mines[i][j] != 0 && !hasMineAt(i, j)) {
							opened[i][j] = true;
						}
						else if (mines[i][j] == 0) {
							if (!opened[i][j]) {
								openCell(i, j);
							}
						}
					}
				}
			}
		}
	}
}

bool Field::isCellOpened(int x, int y)
{
	return opened[x][y];
}

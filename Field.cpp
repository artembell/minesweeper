#include "Field.h"
#include <time.h>

Field::Field(int cols, int rows, int minesAmount) {

	colsAmount = cols;
	rowsAmount = rows;
	minesNumber = minesAmount;

	opened.resize(rowsAmount);
	mines.resize(rowsAmount);
	flags.resize(rowsAmount);

	for (auto i = 0; i < rowsAmount; i++) {
		opened.at(i).resize(colsAmount, false);
		mines.at(i).resize(colsAmount, 0);
		flags.at(i).resize(colsAmount, false);
	}

	initializeMines();
	initializeDigits();
}

int Field::getRowsAmount() {
	return rowsAmount;
}

int Field::getColsAmount() {
	return colsAmount;
}

bool Field::hasMineAt(int x, int y) {
	return mines.at(x).at(y) == MINE;
}

int Field::getDigitAt(int x, int y) {
	return mines.at(x).at(y);
}

void Field::setFlag(int x, int y) {
	if (!isCellOpened(x, y)) {
		flags.at(x).at(y) = !flags.at(x).at(y);
	}
}

bool Field::hasFlagAt(int x, int y) {
	return flags.at(x).at(y);
}

bool Field::isCellOpened(int x, int y) {
	return opened.at(x).at(y);
}

int Field::getFlagsAround(int x, int y) {
	int number = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < 10) {
				if (hasFlagAt(i, j)) {
					number++;
				}
			}
		}
	}

	return number;
}

bool Field::hasCell(int x, int y) {
	return x >= 0 && x <= rowsAmount && y >= 0 && y <= colsAmount;
}

void Field::openAround(int x, int y) {
	if (isCellOpened(x, y)) {
		int digit = getDigitAt(x, y);
		int flags = getFlagsAround(x, y);

		if (digit != 0 && digit == flags) {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					if (i >= 0 && i < 10 && j >= 0 && j < 10) {
						openCell(i, j);
					}
				}
			}
		}
	}
}


void Field::initializeMines() {
	int minesLeft = minesNumber;

	srand(time(0));
	while (minesLeft) {
		int x = rand() % (colsAmount - 1);
		int y = rand() % (rowsAmount - 1);

		if (!mines.at(x).at(y)) {
			mines.at(x).at(y) = MINE;
			minesLeft--;
		}
	}
}

void Field::initializeDigits() {
	for (int i = 0; i < rowsAmount; i++) {
		for (int j = 0; j < colsAmount; j++) {
			if (hasMineAt(i, j)) {
				incrementDigitsAround(i, j);
			}
		}
	}
}

void Field::incrementDigitsAround(int x, int y) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && i < rowsAmount && j >= 0 && j < colsAmount) {
				if (!hasMineAt(i, j)) {
					mines.at(i).at(j)++;
				}
			}
		}
	}
}

void Field::openCell(int x, int y) {
	if (!hasFlagAt(x, y)) {
		opened.at(x).at(y) = true;

		if (mines.at(x).at(y) == 0) {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					if (i >= 0 && i < rowsAmount && j >= 0 && j < colsAmount) {
						if (!hasFlagAt(i, j)) {
							if (mines.at(i).at(j) != 0 && !hasMineAt(i, j)) {
								opened.at(i).at(j) = true;
							}
							else if (mines.at(i).at(j) == 0) {
								if (!opened.at(i).at(j)) {
									openCell(i, j);
								}
							}
						}
					}
				}
			}
		}
	}
}
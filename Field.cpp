#include "Field.h"
#include <time.h>

Field::Field(int difficulty) {
	switch (difficulty) {
		case BEGINNER: {
			rowsNumber = 10;
			colsNumber = 10;
			minesNumber = 10;
			break;
		}
		case INTERMEDIATE: {
			rowsNumber = 18;
			colsNumber = 14;
			minesNumber = 40;
			break;
		}
		case EXPERT: {
			rowsNumber = 28;
			colsNumber = 18;
			minesNumber = 99;
			break;
		}
		default:
			break;
	}

	opened.resize(rowsNumber);
	mines.resize(rowsNumber);
	flags.resize(rowsNumber);

	for (int i = 0; i < rowsNumber; i++) {
		opened.at(i).resize(colsNumber, false);
		mines.at(i).resize(colsNumber, 0);
		flags.at(i).resize(colsNumber, false);
	}

	initializeMines();
	initializeDigits();
}

int Field::getRowsNumber() {
	return rowsNumber;
}

int Field::getColsNumber() {
	return colsNumber;
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
	return x >= 0 && x < rowsNumber && y >= 0 && y < colsNumber;
}

void Field::openAround(int x, int y) {
	if (isCellOpened(x, y)) {
		int digit = getDigitAt(x, y);
		int flags = getFlagsAround(x, y);

		if (digit != 0 && digit == flags) {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					if (hasCell(i, j)) {
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
		int x = rand() % (rowsNumber - 1);
		int y = rand() % (colsNumber - 1);

		if (!mines.at(x).at(y)) {
			mines.at(x).at(y) = MINE;
			minesLeft--;
		}
	}
}

void Field::initializeDigits() {
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			if (hasMineAt(i, j)) {
				incrementDigitsAround(i, j);
			}
		}
	}
}

void Field::incrementDigitsAround(int x, int y) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (hasCell(i, j)) {
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
					if (hasCell(i, j)) {
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
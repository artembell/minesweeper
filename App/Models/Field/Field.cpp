#include "Field.h"

Field::Field(int rowsNumber, int colsNumber, int minesNumber) {
	setFieldConfiguration(rowsNumber, colsNumber, minesNumber);
}

void Field::setFieldConfiguration(int rowsNumber, int colsNumber, int minesNumber) {
	this->rowsNumber = rowsNumber;
	this->colsNumber = colsNumber;
	this->minesNumber = minesNumber;

	opened.resize(this->rowsNumber);
	mines.resize(this->rowsNumber);
	flags.resize(this->rowsNumber);

	for (int i = 0; i < this->rowsNumber; i++) {
		opened.at(i).resize(this->colsNumber, false);
		mines.at(i).resize(this->colsNumber, 0);
		flags.at(i).resize(this->colsNumber, false);
	}
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

int Field::setFlag(int x, int y) {
	if (!isCellOpened(x, y)) {
		flags.at(x).at(y) = !flags.at(x).at(y);
		return flags.at(x).at(y) ? 1 : -1;
	}
	return 0;
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
			if (hasCell(i, j)) {
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
	std::cout << x << ", " << y << std::endl;
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

bool Field::hasOpenedMines() {
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			if (isCellOpened(i, j) && hasMineAt(i, j)) {
				return true;
			}
		}
	}
	return false;
}

bool Field::hasFlags() {
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			if (hasFlagAt(i, j)) {
				return true;
			}
		}
	}
	return false;
}

bool Field::hasOpenedCells() {
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			if (isCellOpened(i, j)) {
				return true;
			}
		}
	}
	return false;
}

void Field::generateWithSpaceAround(int x, int y) {
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

void Field::openAllMines() {
	for (int i = 0; i < rowsNumber; i++) {
		for (int j = 0; j < colsNumber; j++) {
			if (hasMineAt(i, j)) {
				opened.at(i).at(j) = true;
			}
		}
	}
}

void Field::initializeMines(int x, int y) {
	int minesLeft = minesNumber;
	int const xOffset = 1, yOffset = 1;

	srand(time(0));
	while (minesLeft) {
		int xRand = rand() % (rowsNumber - 1);
		int yRand = rand() % (colsNumber - 1);
		if (!(x - xOffset <= xRand && xRand <= x + xOffset) ||
			!(y - yOffset <= yRand && yRand <= y + yOffset)) {
			if (!hasMineAt(xRand, yRand)) {
				mines.at(xRand).at(yRand) = MINE;
				minesLeft--;
				std::cout << xRand << ", " << yRand << " - " << minesLeft << std::endl;
			}
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
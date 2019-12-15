#pragma once
#include <vector>

typedef struct _Point {
	int x;
	int y;
} Point;


class Field {
private:
	const int MINE = -1;

	int rowsAmount;
	int colsAmount;
	int minesNumber;

	std::vector<std::vector<int>> mines;
	std::vector<std::vector<bool>> opened;
	std::vector<std::vector<bool>> flags;


	void initializeMines();
	void initializeDigits();
	void incrementDigitsAround(int x, int y);

public:
	Field(int cols = 10, int rows = 10, int minesAmount = 10);
	int getRowsAmount();
	int getColsAmount();

	bool hasMineAt(int x, int y);
	int getDigitAt(int x, int y);

	void setFlag(int x, int y);
	bool hasFlagAt(int x, int y);

	void openCell(int x, int y);
	bool isCellOpened(int x, int y);
	int getFlagsAround(int x, int y);
	bool hasCell(int x, int y);

	void openAround(int x, int y);
};
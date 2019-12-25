#pragma once

#include "../Config/enums.h"
#include "../Config/constants.h"

int getDifficultyRows(Difficulty difficulty);
int getDifficultyCols(Difficulty difficulty);
int getDifficultyMines(Difficulty difficulty);
int getDifficultyCellSize(Difficulty difficulty);
float getDifficultyScaleFactor(Difficulty difficulty);
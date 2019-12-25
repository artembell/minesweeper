#include "Utils.h"

int getDifficultyRows(Difficulty difficulty) {
	switch (difficulty) {
		case BEGINNER: return BEGINNER_ROWS;
		case INTERMEDIATE: return INTERMEDIATE_ROWS;
		case EXPERT: return EXPERT_ROWS;
		default: return BEGINNER_ROWS;
	};
}

int getDifficultyCols(Difficulty difficulty) {
	switch (difficulty) {
		case BEGINNER: return BEGINNER_COLS;
		case INTERMEDIATE: return INTERMEDIATE_COLS;
		case EXPERT: return EXPERT_COLS;
		default: return BEGINNER_COLS;
	};
}

int getDifficultyMines(Difficulty difficulty) {
	switch (difficulty) {
		case BEGINNER: return BEGINNER_MINES;
		case INTERMEDIATE: return INTERMEDIATE_MINES;
		case EXPERT: return EXPERT_MINES;
		default: return BEGINNER_MINES;
	};
}

int getDifficultyCellSize(Difficulty difficulty) {
	switch (difficulty) {
		case BEGINNER: return BEGINNER_CELL_SIZE;
		case INTERMEDIATE: return INTERMEDIATE_CELL_SIZE;
		case EXPERT: return EXPERT_CELL_SIZE;
		default: return BEGINNER_CELL_SIZE;
	};
}

float getDifficultyScaleFactor(Difficulty difficulty) { 
	switch (difficulty) {
		case BEGINNER: return (float)BEGINNER_CELL_SIZE / BEGINNER_CELL_SIZE;
		case INTERMEDIATE: return (float)INTERMEDIATE_CELL_SIZE / BEGINNER_CELL_SIZE;
		case EXPERT: return (float)EXPERT_CELL_SIZE / BEGINNER_CELL_SIZE;
		default: return (float)BEGINNER_CELL_SIZE / BEGINNER_CELL_SIZE;
	};
}

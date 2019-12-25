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
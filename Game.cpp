#include "Game.h"
#include "constants.h"

Game::Game(Difficulty difficulty) {
	switch (difficulty) {
	case BEGINNER: {
		field.setFieldConfiguration(BEGINNER_ROWS, BEGINNER_COLS, BEGINNER_MINES);
		break;
	}
	case INTERMEDIATE: {
		field.setFieldConfiguration(INTERMEDIATE_ROWS, INTERMEDIATE_COLS, INTERMEDIATE_MINES);
		break;
	}
	case EXPERT: {
		field.setFieldConfiguration(EXPERT_ROWS, EXPERT_COLS, EXPERT_MINES);
		break;
	}
	default:
		field.setFieldConfiguration(BEGINNER_ROWS, BEGINNER_COLS, BEGINNER_MINES);
		break;
	};
}

void Game::start() {
	timer.restart();

}

Field* Game::getField() {
	return &field;
}

int Game::getTimeElapsed() {
	return timer.getElapsedTime().asSeconds();
}

GameStatus Game::getGameStatus() {
	bool hasClosedEmpty = false;
	for (int i = 0; i < getField()->getRowsNumber(); i++) {
		for (int j = 0; j < getField()->getColsNumber(); j++) {
			if (getField()->isCellOpened(i, j)) {
				if (getField()->hasMineAt(i, j)) {
					return LOST;
				}
			}
			else {
				if (!getField()->hasMineAt(i, j)) {
					hasClosedEmpty = true;
				}
			}
		}
	}

	return hasClosedEmpty ? IN_PROCESS : WON;
}

Difficulty Game::getDifficulty() {
	return Difficulty();
}

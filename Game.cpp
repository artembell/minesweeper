#include "Game.h"
#include "constants.h"
#include <iostream>

Game::Game(Difficulty difficulty) {
	switch (difficulty) {
	case BEGINNER: {
		field.setFieldConfiguration(BEGINNER_ROWS, BEGINNER_COLS, BEGINNER_MINES);
		flagsLeft = BEGINNER_MINES;
		break;
	}
	case INTERMEDIATE: {
		field.setFieldConfiguration(INTERMEDIATE_ROWS, INTERMEDIATE_COLS, INTERMEDIATE_MINES);
		flagsLeft = INTERMEDIATE_MINES;
		break;
	}
	case EXPERT: {
		field.setFieldConfiguration(EXPERT_ROWS, EXPERT_COLS, EXPERT_MINES);
		flagsLeft = EXPERT_MINES;
		break;
	}
	default:
		field.setFieldConfiguration(BEGINNER_ROWS, BEGINNER_COLS, BEGINNER_MINES);
		flagsLeft = BEGINNER_MINES;
		break;
	};
}

void Game::restart() {
	timer.restart();
}

void Game::configure() {

}

Field* Game::getField() {
	return &field;
}

int Game::getTimeElapsed() {
	return timer.getElapsedTime().asSeconds();
}

int Game::getFlagsLeft() {
	return flagsLeft;
}

bool Game::hasStarted() {
	return getGameStatus() != NOT_STARTED;
}

void Game::setFlag(int x, int y) {
	int setFlagStatus = field.setFlag(x, y);
	if (setFlagStatus > 0) {
		flagsLeft--;
	} else if (setFlagStatus < 0) {
		flagsLeft++;
	};
}

GameStatus Game::getGameStatus() {
	bool hasClosedEmpty = false;
	// if zero flags and zero opened
	if (!field.hasOpenedCells() && !field.hasFlags()) {
		std::cout << "NOT STARTED" << std::endl;
		return NOT_STARTED;
		
	}
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

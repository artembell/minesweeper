#include "Game.h"

Game::Game(Difficulty difficulty) 
	: field(getDifficultyRows(difficulty), getDifficultyCols(difficulty), getDifficultyMines(difficulty)),
	gameDifficulty(difficulty) {

	flagsLeft = getDifficultyMines(difficulty);
	resultGameTime = 0;
}

void Game::restart() {
	resultGameTime = getTimeElapsed();
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

int Game::getResultTime() {
	return resultGameTime;
}

int Game::getFlagsLeft() {
	return flagsLeft;
}

void Game::saveResultTime() {
	resultGameTime = getTimeElapsed();
}

bool Game::hasStarted() {
	return getGameStatus() != NOT_STARTED;
}

void Game::setFlag(int x, int y) {
	if (!field.isCellOpened(x, y)) {
		field.hasFlagAt(x, y) ? flagsLeft++ : flagsLeft--;
		field.toggleFlag(x, y);
	}
}

GameStatus Game::getGameStatus() {
	bool hasClosedEmpty = false;
	// if zero flags and zero opened
	if (!field.hasOpenedCells() && !field.hasFlags() || timer.getElapsedTime().asMilliseconds() == 0) {
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
	return gameDifficulty;
}

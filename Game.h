#pragma once

#include "enums.h"
#include "Field.h"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game(Difficulty difficulty);
	void restart();
	void configure();

	int getTimeElapsed();
	int getFlagsLeft();
	bool hasStarted();

	void setFlag(int x, int y);

	Field* getField();
	Difficulty getDifficulty();
	GameStatus getGameStatus();
private:
	Field field;
	sf::Clock timer;
	int flagsLeft;
	GameStatus gameStatus;
	Difficulty difficulty;
};
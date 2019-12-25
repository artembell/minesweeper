#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Field/Field.h"
#include "../../Utils/Utils.h"
#include "../../Config/enums.h"
#include "../../Config/constants.h"

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
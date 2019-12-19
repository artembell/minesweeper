#pragma once

#include "enums.h"
#include "Field.h"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game(Difficulty difficulty);
	void start();

	int getTimeElapsed();

	Field* getField();
	Difficulty getDifficulty();
	GameStatus getGameStatus();
private:
	Field field;
	
	sf::Clock timer;
	GameStatus gameStatus;
	Difficulty difficulty;
};
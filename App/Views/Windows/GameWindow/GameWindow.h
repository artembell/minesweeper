#pragma once

#include <iostream>
#include "../CustomWindow/CustomWindow.h"
#include "../StartWindow/StartWindow.h"
#include "../../../Models/Field/Field.h"
#include "../../../Models/Game/Game.h"
#include "../../../Config/enums.h"
#include "../../../Config/constants.h"


class GameWindow : public CustomWindow {
public:
	GameWindow(Difficulty difficulty);
	void render() override;
private:
	Game game;
	
	sf::RectangleShape closedCell;
	sf::Texture mineTexture, flagTexture, timerTexture;
	sf::Sprite mineSprite, flagSprite, timerSprite, flagsLeftSprite;
	sf::Font gameFont;
	sf::Text digitText, timerText, flagsLeftText, statusText;

	std::vector<sf::Color> colors;
	std::vector<std::vector<int>> highlightedField;
	std::vector<std::vector<std::vector<int>>> viewColors;
	
	sf::Vector2i mousePosition, fieldSize, fieldCoords;

	float scaleFactor;
	int xField, yField, cellSize, mineRadius;
	bool isGameOver;

	void initResources() override;
	void checkActions() override;

	bool isClickOnField(sf::Vector2i position);

	void drawField();
	void drawCell(int i, int j);
	void setCellColors();
	void highlightAround(int x, int y);
	void highlightCell(int x, int y);
	void unhighlightAll();
	void prepareTimer();
	void prepareFlagsLeftText();
};
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

	float scaleFactor;
	Game game;

	void initResources() override;
	void checkActions() override;	
	
	sf::Texture mineTexture, flagTexture, timerTexture;
	sf::Sprite mineSprite, flagSprite, timerSprite, flagsLeftSprite;
	sf::Font gameFont;
	sf::Text digitText, timerText, flagsLeftText, statusText;

	std::vector<sf::Color> colors;
	std::vector<std::vector<int>> highlightedField;

	std::vector<std::vector<std::vector<int>>> viewColors;
	int prevColor;
	sf::Vector2i mousePosition;

	sf::RectangleShape closedCell;

	sf::Vector2i fieldSize, fieldCoords;


	int xField, yField, cellSize, mineRadius;
	bool isGameOver;

	bool isClickOnField(sf::Vector2i position);
	void drawField();
	void drawCell(int i, int j);
	

	void setCellColors();
	void highlightAround(int x, int y);
	void highlightCell(int x, int y);


	void unhighlightAll();
};
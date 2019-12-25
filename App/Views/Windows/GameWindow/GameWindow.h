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
	
	sf::Text timerText, flagsLeftText;

	//sf::RenderWindow window;
	std::vector<sf::Color> colors;
	std::vector<std::vector<int>> highlightedField;

	std::vector<std::vector<std::vector<int>>> viewColors;
	int prevColor;
	sf::Vector2i mousePosition;

	sf::RectangleShape closedCell;


	sf::Texture mineTexture, flagTexture;
	sf::Sprite mineSprite, flagSprite;

	sf::Font digitFont;
	sf::Text digitText;

	//Field field;
	// field viewport
	int xField, yField, cellSize, mineRadius;
	bool isGameOver;

	
	void drawField();
	void drawCell(int i, int j);
	

	void setCellColors();
	void highlightAround(int x, int y);
	void highlightCell(int x, int y);


	void unhighlightAll();
};
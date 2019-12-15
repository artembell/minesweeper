#pragma once
#include "CustomWindow.h"
#include "Field.h"

class GameWindow {
public:
	// in parent should be
	GameWindow(sf::String title);
	// in parent should be
	void render();
private:
	enum ButtonState { PRESSED = 1, RELEASED = 0 };
	// in parent should be
	bool leftButton, rightButton;


	sf::RenderWindow window;
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

	Field field;
	// field viewport
	int xField, yField, cellSize, mineRadius;
	bool isGameOver;

	// in parent should be
	void initResources();
	void drawField();
	void drawCell(int i, int j);
	
	// in parent should be
	void checkActions();

	void setCellColors();
	void highlightAround(int x, int y);
	void highlightCell(int x, int y);

	void unhighlightAll();
};
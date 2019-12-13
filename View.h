#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include <vector>

class View {

public:
	View();
	void init();

	void OpenSettingsWindow();
	void OpendRecordsWindow();
private:
	Field field;
	int cellSize;
	int mineRadius;
	bool isGameOver;

	sf::RenderWindow window;
	std::vector<sf::Color> colors;

	// resources for drawing
	sf::RectangleShape closedCell;

	sf::Texture mineTexture, flagTexture;
	sf::Sprite mineSprite, flagSprite;

	sf::Font digitFont;
	sf::Text digitText;
	// ----------------------

	Point getCell(int x, int y);
	
	void drawField();
	void drawCell(int i, int j);
	void initResources();
};


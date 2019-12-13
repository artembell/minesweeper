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
	sf::RenderWindow window;
	std::vector<sf::Color> colors;

	// resources for drawing
	sf::RectangleShape closedCell;

	sf::Texture mineTexture, flagTexture;
	sf::Sprite mineSprite, flagSprite;

	sf::Font digitFont;
	sf::Text digitText;
	// ----------------------


	int cellSize;
	int mineRadius;
	bool isGameOver;



	Point getCell(int x, int y);
	Field field;
	void drawField();
	void drawCell(int rowIndex, int colIndex);
	void initResources();
};


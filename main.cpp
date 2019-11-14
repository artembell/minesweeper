#include <SFML/Graphics.hpp>

#include "Field.h"
#include <iostream>
#include <string.h>

Field field;
int cellSize = 50;
int mineRadius = 20;
int isGameOver = false;

void drawField(sf::RenderWindow* window) {
	
	bool change = false;

	sf::Font font;
	font.loadFromFile("my-font.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::RectangleShape closedCell(sf::Vector2f(50, 50));
	sf::CircleShape mineCell;
	mineCell.setRadius(mineRadius);
	mineCell.setFillColor(sf::Color(10, 10, 10));


	//sf::Texture mineTexture;
	//mineTexture.loadFromFile("mine1.jpg");

	for (int i = 0; i < field.getRowsAmount(); i++) {
		for (int j = 0; j < field.getColsAmount(); j++) {

			change ? closedCell.setFillColor(sf::Color(83, 198, 83)) : closedCell.setFillColor(sf::Color(121, 210, 121));
			closedCell.setPosition(i * cellSize, j * cellSize);
			window->draw(closedCell);

			if (field.isCellOpened(i, j)) {
				closedCell.setFillColor(sf::Color(191, 191, 191));
				window->draw(closedCell);

				if (field.hasMineAt(i, j)) {
					mineCell.setPosition(i * cellSize + (cellSize - 2 * mineRadius) / 2, j * cellSize + (cellSize - 2 * mineRadius) / 2);
					window->draw(mineCell);
				}
				else {
					// draw digit
					// set the string to display
					int digit = field.getDigitAt(i, j);
					if (digit != 0) {
						text.setString(std::to_string(digit));
						text.setPosition(i * cellSize, j * cellSize);
						window->draw(text);
					}		
				}
			}
			change = !change;
		}
		change = !change;
	}
}

Point getCell(float x, float y) {

	Point point;
	point.x = (int) (x / cellSize);
	point.y = (int) (y / cellSize);

	return point;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen() && !isGameOver)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					//std::cout << "right" << std::endl;
					Point p = getCell(event.mouseButton.x, event.mouseButton.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					//std::cout << "left" << std::endl;

					Point p = getCell(event.mouseButton.x, event.mouseButton.y);
					field.openCell(p.x, p.y);

					if (field.hasMineAt(p.x, p.y)) {
						std::cout << "GAME OVER" << std::endl;
						isGameOver = true;
					}
				}
			}

		}

		window.clear(sf::Color(255, 255, 255));
		drawField(&window);
		window.display();
	}

	return 0;
}


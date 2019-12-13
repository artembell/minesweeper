#include "View.h"
#include <string>
#include <iostream>

View::View() : 
	window(sf::VideoMode(500, 500), "Minesweeper"),
	closedCell(sf::RectangleShape(sf::Vector2f(50, 50))),
	field(10, 10, 10) {}

Point View::getCell(int x, int y)
{
	Point point;
	point.x = (int)(x / cellSize);
	point.y = (int)(y / cellSize);

	return point;
}


void View::init() {
	
	cellSize = 50;
	mineRadius = 20;

	initResources();

	isGameOver = false;
	while (window.isOpen() && !isGameOver)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				//OpendRecordsWindow();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "right" << std::endl;
					Point p = getCell(event.mouseButton.x, event.mouseButton.y);
					field.setFlag(p.x, p.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "left" << std::endl;

					Point p = getCell(event.mouseButton.x, event.mouseButton.y);
					if (!field.hasFlagAt(p.x, p.y)) {
						field.openCell(p.x, p.y);
					}

					if (field.hasMineAt(p.x, p.y)) {
						//std::cout << "GAME OVER" << std::endl;
						//isGameOver = true;
					}
				}
			}
		}


		window.clear(sf::Color(255, 255, 255));

		// void drawField
		drawField();
		// void drawField

		window.display();
	}
}

void View::OpenSettingsWindow() {
	sf::Window settingsWindow;
	settingsWindow.create(sf::VideoMode(500, 500), "Settings");

	while (settingsWindow.isOpen()) {
		sf::Event event;
		while (settingsWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				settingsWindow.close();
		}
	}
}

void View::OpendRecordsWindow() {
	sf::Window recordsWindow;
	recordsWindow.create(sf::VideoMode(800, 500), "Records");

	while (recordsWindow.isOpen()) {
		sf::Event event;
		while (recordsWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				recordsWindow.close();
		}
	}
}



void View::drawField() {
	bool change = false;
	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			drawCell(i, j);

			change ?
				closedCell.setFillColor(sf::Color(83, 198, 83)) :
				closedCell.setFillColor(sf::Color(121, 210, 121));

			change = !change;
		}
		change ?
			closedCell.setFillColor(sf::Color(83, 198, 83)) :
			closedCell.setFillColor(sf::Color(121, 210, 121));
		change = !change;
	}
}

void View::initResources() {
	digitFont.loadFromFile("main-font.ttf");
	digitText.setFont(digitFont);
	digitText.setCharacterSize(50);

	mineTexture.loadFromFile("mine2.png", sf::IntRect(0, 0, 300, 300));
	mineSprite.setTexture(mineTexture);

	flagTexture.loadFromFile("flag1.png", sf::IntRect(0, 0, 300, 300));
	flagSprite.setTexture(flagTexture);
}


void View::drawCell(int rowIndex, int colIndex) {
	int i = rowIndex;
	int j = colIndex;

	closedCell.setPosition(i * cellSize, j * cellSize);
	window.draw(closedCell);

	if (field.isCellOpened(i, j)) {
		if (field.hasMineAt(i, j)) {
			mineSprite.setPosition(i * cellSize, j * cellSize);
			window.draw(mineSprite);
		}
		else {
			int digit = field.getDigitAt(i, j);
			//digitText.setFillColor(colors[digit - 1]);
			digitText.setFillColor(sf::Color::Red);
			if (digit != 0) {
				digitText.setString(std::to_string(digit));
				digitText.setPosition(i * cellSize + 10, j * cellSize - 10);
				window.draw(digitText);
			}
		}
	}
	else if (field.hasFlagAt(i, j)) {
		flagSprite.setPosition(i * cellSize, j * cellSize);
		window.draw(flagSprite);
	}
}


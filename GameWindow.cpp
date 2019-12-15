#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(sf::String title) :
	window(sf::VideoMode(500, 500), title),
	closedCell(sf::RectangleShape(sf::Vector2f(50, 50))),
	field(10, 10, 10)
{
	
}


void GameWindow::render() {
	cellSize = 50;
	mineRadius = 20;
	initResources();
	isGameOver = false;

	while (window.isOpen() && !isGameOver) {
		checkActions();
		window.clear(sf::Color(255, 255, 255));
		drawField();
		window.display();
	}
}

void GameWindow::initResources() {
	highlightedField.resize(10);
	viewColors.resize(10);
	for (int i = 0; i < 10; i++) {
		highlightedField.at(i).resize(10);
		viewColors.at(i).resize(10);

		for (int j = 0; j < 10; j++) {
			viewColors.at(i).at(j).resize(2);
		}
	}
	setCellColors();

	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Black);

	digitFont.loadFromFile("main-font.ttf");
	digitText.setFont(digitFont);
	digitText.setCharacterSize(50);

	mineTexture.loadFromFile("mine2.png", sf::IntRect(0, 0, 300, 300));
	mineSprite.setTexture(mineTexture);

	flagTexture.loadFromFile("flag1.png", sf::IntRect(0, 0, 300, 300));
	flagSprite.setTexture(flagTexture);

	leftButton = rightButton = RELEASED;
	mousePosition = sf::Vector2i(0, 0);
	prevColor = 1; 
}


void GameWindow::checkActions() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}

	sf::Vector2i hoverMousePos = sf::Mouse::getPosition(window);
	int xHover = (int)(hoverMousePos.x / cellSize);
	int yHover = (int)(hoverMousePos.y / cellSize);

	sf::Vector2i oldMousePos = mousePosition;
	int xOld = oldMousePos.x;
	int yOld = oldMousePos.y;
	mousePosition = sf::Vector2i(xHover, yHover);

	bool oldLeftButton = leftButton,
		oldRightLeftButton = rightButton;

	leftButton = rightButton = RELEASED;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) leftButton = PRESSED;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) rightButton = PRESSED;

	// check for clicking in this window!!!
	
	if (oldLeftButton == RELEASED && oldRightLeftButton == RELEASED) {
		if (leftButton == PRESSED && rightButton == RELEASED) {
			field.openCell(xHover, yHover);
		} else if (leftButton == RELEASED && rightButton == PRESSED) {
			field.setFlag(xHover, yHover);
		}
	} else if (oldLeftButton == PRESSED && oldRightLeftButton == PRESSED) {
		if (leftButton == RELEASED && rightButton == PRESSED) {
			std::cout << "OPEN" << std::endl;
		}
		if (leftButton == RELEASED || rightButton == RELEASED) {
			unhighlightAll();
			highlightCell(xHover, yHover);
		}
	} else if ((oldLeftButton == PRESSED && oldRightLeftButton == RELEASED) ||
		(oldLeftButton == RELEASED && oldRightLeftButton == PRESSED)) {
		if (leftButton == PRESSED && rightButton == PRESSED) {
			highlightAround(xHover, yHover);
		}
	}

	if (xHover != xOld || yHover != yOld) {
		unhighlightAll();
		highlightCell(xHover, yHover);
		if (oldLeftButton == PRESSED && oldRightLeftButton == PRESSED) {
			if (leftButton == PRESSED && rightButton == PRESSED) {
				highlightAround(xHover, yHover);
			}
		}
	}
}


void GameWindow::drawField() {
	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			drawCell(i, j);
		}
	}
}

void GameWindow::drawCell(int i, int j) {\
	sf::Color color;
	if (viewColors.at(i).at(j).at(0) == 1) {
		if (viewColors.at(i).at(j).at(1) == 3) {
			color = sf::Color(185, 222, 119);
		}
		else {
			color = sf::Color(162, 208, 73);
		}
	} else if (viewColors.at(i).at(j).at(0) == 2) {
		if (viewColors.at(i).at(j).at(1) == 3) {
			color = sf::Color(190, 225, 125);
		}
		else {
			color = sf::Color(169, 215, 81);
		}
	}

	closedCell.setFillColor(color);
	closedCell.setPosition(i * cellSize, j * cellSize);
	window.draw(closedCell);

	if (field.isCellOpened(i, j)) {
		if (viewColors.at(i).at(j).at(0) == 1) {
			color = sf::Color(215, 184, 153);
		}
		else if (viewColors.at(i).at(j).at(0) == 2) {
			color = sf::Color(228, 194, 159);
		}
		closedCell.setFillColor(color);
		closedCell.setPosition(i * cellSize, j * cellSize);
		window.draw(closedCell);

		if (field.hasMineAt(i, j)) {
			mineSprite.setPosition(i * cellSize, j * cellSize);
			window.draw(mineSprite);
		}
		else {
			int digit = field.getDigitAt(i, j);
			if (digit != 0) {
				digitText.setFillColor(colors.at(digit - 1));
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

void GameWindow::setCellColors() {
	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();
	bool change = false;

	const int FIRST_COLOR = 1;
	const int SECOND_COLOR = 2;
	/*sf::Color color1(83, 198, 83),
		color2(121, 210, 121),
		currentCellColor = color1;*/
	int currentCellColor;
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			currentCellColor = change ? FIRST_COLOR : SECOND_COLOR;
			viewColors.at(i).at(j).at(0) = currentCellColor;
			viewColors.at(i).at(j).at(1) = currentCellColor;
			change = !change;
		}

		if (colCount % 2 == 0) {
			change = !change;
		}
	}
}

void GameWindow::highlightAround(int x, int y) {
	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();

	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && i < rowCount && j >= 0 && j < colCount) {
				highlightCell(i, j);
			}
		}
	}
}

void GameWindow::highlightCell(int x, int y) {
	viewColors.at(x).at(y).at(1) = 3;
}

void GameWindow::unhighlightAll() {
	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			viewColors.at(i).at(j).at(1) = viewColors.at(i).at(j).at(0);
		}
	}
}

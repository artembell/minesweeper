#include "View.h"

View::View()
{
	//sf::RenderWindow window;
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
}

void View::init()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	Field field;
	cellSize = 50;
	mineRadius = 20;

	initResources();

	isGameOver = false;
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
					field.setFlag(p.x, p.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					//std::cout << "left" << std::endl;

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
		//drawField();

		//sf::CircleShape shape(50.f);
		//shape.setFillColor(sf::Color(100, 250, 50));
		
		//closedCell.setPosition(1 * cellSize, 1 * cellSize);
		sf::RectangleShape closedCell1(sf::Vector2f(50, 50));
		closedCell1.setPosition(0 * cellSize, 0 * cellSize);
		closedCell1.setFillColor(sf::Color(83, 198, 83));
		window.draw(closedCell1);
		window.display();
	}
}

Point View::getCell(int x, int y)
{
	Point point;
	point.x = (int)(x / cellSize);
	point.y = (int)(y / cellSize);

	return point;
}

void View::drawField() {
	bool change = false;

	int rowCount = field.getRowsAmount(),
		colCount = field.getColsAmount();
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			//drawCell(i, j);
			closedCell.setPosition(i * cellSize, j * cellSize);
			window.draw(closedCell);
			change ? 
				closedCell.setFillColor(sf::Color(83, 198, 83)) : 
				closedCell.setFillColor(sf::Color(121, 210, 121));
			change = !change;
		}
		change = !change;
	}
}

void View::drawCell(int rowIndex, int colIndex) {
	closedCell.setPosition(rowIndex * cellSize, colIndex * cellSize);
	window.draw(closedCell);

	if (field.isCellOpened(rowIndex, colIndex)) {
		closedCell.setFillColor(sf::Color(191, 191, 191));
		window.draw(closedCell);

		if (field.hasMineAt(rowIndex, colIndex)) {
			mineSprite.setPosition(rowIndex * cellSize, colIndex * cellSize);
			//window->draw(mineCell);
			window.draw(mineSprite);
		}
		else {
			// draw digit
			// set the string to display
			int digit = field.getDigitAt(rowIndex, colIndex);
			//digitText.setFillColor(colors[digit - 1]);
			digitText.setFillColor(sf::Color::Red);
			if (digit != 0) {
				digitText.setString(std::to_string(digit));
				digitText.setPosition(rowIndex * cellSize + 10, colIndex * cellSize - 10);
				window.draw(digitText);
			}
		}
	}
	else if (field.hasFlagAt(rowIndex, colIndex)) {
		flagSprite.setPosition(rowIndex * cellSize, colIndex * cellSize);
		window.draw(flagSprite);
	}
}

void View::initResources() {
	digitFont.loadFromFile("main-font.ttf");
	digitText.setFont(digitFont);
	digitText.setCharacterSize(50);

	sf::RectangleShape closedCell(sf::Vector2f(50, 50));

	mineTexture.loadFromFile("mine2.png", sf::IntRect(0, 0, 300, 300));
	mineSprite.setTexture(mineTexture);

	flagTexture.loadFromFile("flag1.png", sf::IntRect(0, 0, 300, 300));
	flagSprite.setTexture(flagTexture);
}

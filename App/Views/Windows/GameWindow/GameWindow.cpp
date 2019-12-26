#include "GameWindow.h"

GameWindow::GameWindow(Difficulty difficulty) 
	: CustomWindow(),
	game(difficulty) {
	cellSize = getDifficultyCellSize(difficulty);
	scaleFactor = getDifficultyScaleFactor(difficulty);

	int rowsCount = game.getField()->getRowsNumber(),
		colsCount = game.getField()->getColsNumber();

	fieldSize = sf::Vector2i(rowsCount * cellSize, colsCount * cellSize);
	window.create(sf::VideoMode(fieldSize.x, fieldSize.y + PANEL_HEIGHT), "Minesweeper", sf::Style::Close);
	leftButtonState = rightButtonState = RELEASED;
	
	initResources();
}

void GameWindow::render() {
	while (window.isOpen()) {
		window.clear(sf::Color(64, 107, 76));
		drawField();

		checkActions();
		window.display();
	} 
}

void GameWindow::initResources() {
	int rowsCount = game.getField()->getRowsNumber(),
		colsCount = game.getField()->getColsNumber();

	highlightedField.resize(rowsCount);
	viewColors.resize(rowsCount);
	for (int i = 0; i < rowsCount; i++) {
		highlightedField.at(i).resize(colsCount);
		viewColors.at(i).resize(colsCount);

		for (int j = 0; j < colsCount; j++) {
			viewColors.at(i).at(j).resize(2);
		}
	}

	setCellColors();

	closedCell.setSize(sf::Vector2f(cellSize, cellSize));
	colors = {
		sf::Color::Blue,
		sf::Color::Green,
		sf::Color::Red,
		sf::Color::Cyan,
		sf::Color::Magenta,
		sf::Color::Black,
		sf::Color::Black,
		sf::Color::Black
	};

	gameFont.loadFromFile("Assets/main_font.ttf");

	digitText.setFont(gameFont);
	digitText.setCharacterSize(cellSize);
	digitText.scale(sf::Vector2f(scaleFactor, scaleFactor));

	statusText.setFont(gameFont);
	statusText.setCharacterSize(FONT_SIZE);

	timerText.setFont(gameFont);
	timerText.setCharacterSize(FONT_SIZE);
	timerText.setFillColor(sf::Color::White);

	flagsLeftText.setFont(gameFont);
	flagsLeftText.setCharacterSize(FONT_SIZE);
	flagsLeftText.setFillColor(sf::Color::White);

	mineTexture.loadFromFile("Assets/mine_texture.png");
	mineTexture.setSmooth(true);
	mineSprite.setTexture(mineTexture);
	mineSprite.scale(sf::Vector2f(scaleFactor, scaleFactor));

	flagTexture.loadFromFile("Assets/flag_texture.png");
	flagTexture.setSmooth(true);
	flagSprite.setTexture(flagTexture);
	flagSprite.scale(sf::Vector2f(scaleFactor, scaleFactor));

	fieldCoords = sf::Vector2i(0, 0);
	mousePosition = sf::Vector2i(0, 0);

	timerTexture.loadFromFile("Assets/Timer.png");
	timerTexture.setSmooth(true);
	timerSprite.setTexture(timerTexture);
	timerSprite.setScale(0.46, 0.46);
	timerSprite.setPosition(sf::Vector2f(window.getSize().x - 180, window.getSize().y - 72));

	flagsLeftSprite.setTexture(flagTexture);
	flagsLeftSprite.setPosition(10, window.getSize().y - 68);
	flagsLeftSprite.setScale(sf::Vector2f(1.2, 1.2));
}

bool GameWindow::isClickOnField(sf::Vector2i position) {
	return (fieldCoords.x < position.x)
		&& (fieldCoords.x + fieldSize.x > position.x)
		&& (fieldCoords.x < position.y)
		&& (fieldCoords.x + fieldSize.y > position.y);
}

void GameWindow::drawField() {
	for (int i = 0; i < game.getField()->getRowsNumber(); i++) {
		for (int j = 0; j < game.getField()->getColsNumber(); j++) {
			drawCell(i, j);
		}
	}
	
	window.draw(timerSprite);
	window.draw(flagsLeftSprite);

	flagsLeftText.setString(std::to_string(game.getFlagsLeft()));
	flagsLeftText.setPosition(70, window.getSize().y - 72);
	window.draw(flagsLeftText);
	
	prepareTimer();
	window.draw(timerText);
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

	if (game.getField()->isCellOpened(i, j)) {
		if (viewColors.at(i).at(j).at(0) == 1) {
			color = sf::Color(215, 184, 153);
		}
		else if (viewColors.at(i).at(j).at(0) == 2) {
			color = sf::Color(228, 194, 159);
		}
		closedCell.setFillColor(color);
		closedCell.setPosition(i * cellSize, j * cellSize);
		window.draw(closedCell);

		if (game.getField()->hasMineAt(i, j)) {
			mineSprite.setPosition(i * cellSize, j * cellSize);
			window.draw(mineSprite);
		}
		else {
			int digit = game.getField()->getDigitAt(i, j);
			if (digit != 0) {
				digitText.setFillColor(colors.at(digit - 1));
				digitText.setString(std::to_string(digit));

				sf::FloatRect textBounds = digitText.getLocalBounds();
				digitText.setOrigin(textBounds.left + textBounds.width / 2.0f,
					textBounds.top + textBounds.height / 2.0f);
				digitText.setPosition(sf::Vector2f(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2));
				window.draw(digitText);
			}
		}
	}
	else if (game.getField()->hasFlagAt(i, j)) {
		flagSprite.setPosition(i * cellSize, j * cellSize);
		window.draw(flagSprite);
	}
}

void GameWindow::setCellColors() {
	int rowCount = game.getField()->getRowsNumber(),
		colCount = game.getField()->getColsNumber();
	bool change = false;

	const int FIRST_COLOR = 1, SECOND_COLOR = 2;

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
	int rowCount = game.getField()->getRowsNumber(),
		colCount = game.getField()->getColsNumber();

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
	int rowCount = game.getField()->getRowsNumber(),
		colCount = game.getField()->getColsNumber();

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			viewColors.at(i).at(j).at(1) = viewColors.at(i).at(j).at(0);
		}
	}
}

void GameWindow::prepareTimer() {
	timerText.setPosition(window.getSize().x - 110, window.getSize().y - 72);

	if ((game.getGameStatus() == NOT_STARTED) || (game.getGameStatus() == LOST) || (game.getGameStatus() == WON)) {
		timerText.setString(std::to_string(game.getResultTime()));
	} else if (game.getGameStatus() == IN_PROCESS) {
		game.saveResultTime();
		timerText.setString(std::to_string(game.getTimeElapsed()));
	}
}

void GameWindow::checkActions() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			StartWindow startWindow;
			startWindow.render();
		}
	}

	sf::Vector2i hoverMousePos = sf::Mouse::getPosition(window);
	std::cout << hoverMousePos.x << std::endl;
	int xHover = (int)(hoverMousePos.x / cellSize);
	int yHover = (int)(hoverMousePos.y / cellSize);

	sf::Vector2i oldMousePos = mousePosition;
	int xOld = oldMousePos.x;
	int yOld = oldMousePos.y;
	mousePosition = sf::Vector2i(xHover, yHover);

	bool oldLeftButton = leftButtonState,
		oldRightLeftButton = rightButtonState;

	leftButtonState = rightButtonState = RELEASED;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) leftButtonState = PRESSED;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) rightButtonState = PRESSED;

	GameStatus currentGameStatus = game.getGameStatus();
	if (currentGameStatus == IN_PROCESS) {
		if (isClickOnField(hoverMousePos)) {
			if (oldLeftButton == RELEASED && oldRightLeftButton == RELEASED) {
				if (leftButtonState == PRESSED && rightButtonState == RELEASED) {

					game.getField()->openCell(xHover, yHover);
				}
				else if (leftButtonState == RELEASED && rightButtonState == PRESSED) {
					game.setFlag(xHover, yHover);
				}
			}
			else if (oldLeftButton == PRESSED && oldRightLeftButton == PRESSED) {
				if (leftButtonState == RELEASED || rightButtonState == RELEASED) {
					game.getField()->openAround(xHover, yHover);
					unhighlightAll();
					highlightCell(xHover, yHover);
				}
			}
			else if ((oldLeftButton == PRESSED && oldRightLeftButton == RELEASED) ||
				(oldLeftButton == RELEASED && oldRightLeftButton == PRESSED)) {
				if (leftButtonState == PRESSED && rightButtonState == PRESSED) {
					highlightAround(xHover, yHover);
				}
			}

			if (xHover != xOld || yHover != yOld) {
				unhighlightAll();
				highlightCell(xHover, yHover);
				if (oldLeftButton == PRESSED && oldRightLeftButton == PRESSED) {
					if (leftButtonState == PRESSED && rightButtonState == PRESSED) {
						highlightAround(xHover, yHover);
					}
				}
			}
		}
	} else if (currentGameStatus == NOT_STARTED) {
		if (isClickOnField(hoverMousePos)) {
			unhighlightAll();
			highlightCell(xHover, yHover);
			game.restart();
			if (leftButtonState == PRESSED) {
				game.getField()->initializeMines(xHover, yHover);
				game.getField()->initializeDigits();
				game.getField()->openCell(xHover, yHover);
			}
			else if (rightButtonState == PRESSED) {
				game.setFlag(xHover, yHover);
			}
		}
	}
	else {
		if (currentGameStatus == LOST) {
			game.getField()->openAllMines();
			statusText.setFillColor(sf::Color::Red);
			statusText.setString("Looser!");
		} else {
			statusText.setFillColor(sf::Color(9, 255, 0));
			statusText.setString("Winner!");
		}
		
		sf::FloatRect textBounds = statusText.getLocalBounds();
		statusText.setOrigin(textBounds.left + textBounds.width / 2.0f,
			textBounds.top + textBounds.height / 2.0f);
		statusText.setPosition(sf::Vector2f(cellSize * game.getField()->getColsNumber() / 2 - 30, window.getSize().y - 40));
		window.draw(statusText);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			StartWindow startWindow;
			startWindow.render();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			window.close();
			GameWindow gameWindow(game.getDifficulty());
			gameWindow.render();
		}
	}
}
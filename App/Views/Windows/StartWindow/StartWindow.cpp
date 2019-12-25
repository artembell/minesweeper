#include "StartWindow.h"

StartWindow::StartWindow()
	: CustomWindow() {
	leftButtonState = RELEASED;
	initResources();
}

void StartWindow::initResources() {
	fileNames = {
		"Assets/Buttons/Beginner.png",
		"Assets/Buttons/Intermediate.png",
		"Assets/Buttons/Expert.png",
		"Assets/Buttons/Exit.png",
		"Assets/Logo.png"
	};

	buttonTextures.resize(START_WINDOW_BUTTONS_NUMBER + 1);
	buttonSprites.resize(START_WINDOW_BUTTONS_NUMBER + 1);
	buttonCoords.resize(START_WINDOW_BUTTONS_NUMBER);

	if (!logoTexture.loadFromFile(fileNames.at(4), sf::IntRect(0, 0, 500, 300))) {
		std::cout << "bad filename" << std::endl;
	}
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(sf::Vector2f(5, 5));

	int x = 100, y = 200;
	for (int i = 0; i < START_WINDOW_BUTTONS_NUMBER; i++) {
		buttonCoords.at(i) = sf::Vector2i(x, y);
		if (!buttonTextures.at(i).loadFromFile(fileNames.at(i), sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) {
			std::cout << "bad filename" << std::endl;
		}
		buttonSprites.at(i).setTexture(buttonTextures.at(i));
		buttonSprites.at(i).setPosition(sf::Vector2f(x, y));
		y += 60;
	}
}

void StartWindow::checkActions() {
	ButtonState oldButtonState = leftButtonState;

	leftButtonState = RELEASED;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) leftButtonState = PRESSED;

	if (oldButtonState == PRESSED) {
		if (leftButtonState == RELEASED) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			
			int index = getButtonId(position);
			switch (index) {
				case 0: 
				case 1: 
				case 2: {
					window.close();
					GameWindow gameWindow((Difficulty)index);
					gameWindow.render();
					break;
				}			
				case 3: window.close();
			}
		}
	}
}

int StartWindow::getButtonId(sf::Vector2i position) {
	for (int i = 0; i < START_WINDOW_BUTTONS_NUMBER; i++) {
		if ((buttonCoords.at(i).x <= position.x)
			&& (buttonCoords.at(i).x + BUTTON_WIDTH >= position.x)
			&& (buttonCoords.at(i).y <= position.y)
			&& (buttonCoords.at(i).y + BUTTON_HEIGHT >= position.y)) {
			return i;
		}
	}
}


void StartWindow::render() {
	while (window.isOpen()) {
		checkActions();
		
		window.clear(sf::Color(255, 255, 200));
		window.draw(logoSprite);
		for (int i = 0; i < START_WINDOW_BUTTONS_NUMBER; i++) {
			window.draw(buttonSprites.at(i));
		}
		
		window.display();
	}
}


#include "Button.h"
#include <iostream>

void Button::calculateTextPosition() {
	buttonText.setPosition(x + 5, y + 5);
}

Button::Button(sf::String text) {
	x = 210;
	y = 210;
	height = 50;
	width = 250;

	buttonShape.setFillColor(sf::Color(255, 219, 77));
	buttonShape.setSize(sf::Vector2f(width, height));
	buttonShape.setPosition(x, y);

	buttonFont.loadFromFile("main-font.ttf");
	buttonText.setString(text);
	calculateTextPosition();
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(20);
}

bool Button::mouseInShapeBounds(sf::Vector2i position) {
	return (position.x >= x) && (position.x <= x + width)
		&& (position.y >= y) && (position.y <= y + height);
}

void Button::processClick() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (mouseInShapeBounds(mousePos)) {
		// !!! fix click response
		std::cout << "in bounds" << std::endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "click" << std::endl;
		}
	}
}

void Button::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
	buttonShape.setPosition(x, y);
	calculateTextPosition();
}

void Button::draw(sf::RenderWindow* window) {
	processClick();
	window->draw(buttonShape);
	window->draw(buttonText);
}



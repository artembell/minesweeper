#include "Button.h"
#include <iostream>

void Button::calculateTextPosition() {
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	std::cout << textBounds.width << std::endl;
	buttonText.setPosition(x + (width - textBounds.width) / 2, 
		y + (height - textBounds.height) / 2 - buttonText.getCharacterSize() / 8);
}

Button::Button() {
	x = 210;
	y = 210;
	height = 50;
	width = 300;

	buttonShape.setFillColor(sf::Color(255, 219, 77));
	buttonShape.setSize(sf::Vector2f(width, height));
	buttonShape.setPosition(x, y);

	buttonFont.loadFromFile("Assets/main_font.ttf");
	buttonText.setString("Standard title");
	calculateTextPosition();
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(20);
}

Button::Button(float x, float y, sf::String text) {
	this->x = x;
	this->y = y;
	height = 50;
	width = 300;

	buttonShape.setFillColor(sf::Color(255, 219, 77));
	buttonShape.setSize(sf::Vector2f(width, height));
	buttonShape.setPosition(x, y);

	buttonFont.loadFromFile("Assets/main_font.ttf");
	buttonText.setString(text);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(20);
	buttonText.setFillColor(sf::Color::Black);
	calculateTextPosition();
}

bool Button::mouseInShapeBounds(sf::Vector2i position) {
	return (position.x >= x) && (position.x <= x + width)
		&& (position.y >= y) && (position.y <= y + height);
}

void Button::processClick() {
	std::cout << "click!" << std::endl;
	//sf::Vector2i mousePos = sf::Mouse::getPosition();
	//if (mouseInShapeBounds(mousePos)) {
	//	// !!! fix click response
	//	std::cout << "in bounds" << std::endl;
	//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	//		std::cout << "click" << std::endl;
	//	}
	//}
}

void Button::setText(sf::String text) {
	buttonText.setString(text);
}

void Button::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
	buttonShape.setPosition(x, y);
	calculateTextPosition();
}

void Button::draw(sf::RenderWindow* window) {
	//processClick();
	window->draw(buttonShape);
	window->draw(buttonText);
}
#include "Button.h"

Button::Button(sf::String text) {
	

	buttonShape.setFillColor(sf::Color::White);
	buttonShape.setSize(sf::Vector2f(100, 50));
	buttonShape.setPosition(0, 0);

	buttonFont.loadFromFile("main-font.ttf");
	buttonText.setString(text);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(50);
}

void Button::setPosition(float x, float y) {
	buttonShape.setPosition(x, y);
}

void Button::draw(sf::RenderWindow *window) {
	window->draw(buttonShape);
	window->draw(buttonText);
}



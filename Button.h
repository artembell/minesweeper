#pragma once
#include <SFML/Graphics.hpp>

class Button {

private:
	int x, y, height, width;

	sf::Text buttonText;
	sf::Font buttonFont;
	sf::RectangleShape buttonShape;

	void calculateTextPosition();
public:
	Button(sf::String text);
	
	void setPosition(float x, float y);
	void draw(sf::RenderWindow *window);
};
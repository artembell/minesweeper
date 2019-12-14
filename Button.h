#pragma once
#include <SFML/Graphics.hpp>

class Button {

private:
	int x, y, height, width;

	sf::Text buttonText;
	sf::Font buttonFont;
	sf::RectangleShape buttonShape;

	void calculateTextPosition();
	bool mouseInShapeBounds(sf::Vector2i position);
	void processClick();
public:
	Button(sf::String text);
	
	
	void setPosition(float x, float y);
	void draw(sf::RenderWindow *window);
};
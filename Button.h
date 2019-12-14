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
	Button();
	Button(float x, float y, sf::String text);
	

	bool mouseInShapeBounds(sf::Vector2i position);
	void setText(sf::String);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow *window);
	void processClick();
};
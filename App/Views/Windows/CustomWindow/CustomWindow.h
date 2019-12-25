#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class CustomWindow {
private:
	sf::RenderWindow window;
	//std::vector<Button> controls;

	//void initButtons();
public:
	CustomWindow(sf::String title);
	void render();
};
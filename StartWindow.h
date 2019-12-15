#pragma once
#include "CustomWindow.h"
#include <vector>
#include "Button.h"

class StartWindow {
private:
	sf::RenderWindow window;
	std::vector<Button> m_buttons;
public:

	StartWindow();
	void render();
};
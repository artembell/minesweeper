#pragma once
#include "CustomWindow.h"
#include <vector>
#include "Button.h"
#include "enums.h"

class StartWindow {
private:
	sf::RenderWindow window;
	std::vector<Button> m_buttons;
	ButtonState buttonState;
public:

	
	StartWindow();
	void render();

};
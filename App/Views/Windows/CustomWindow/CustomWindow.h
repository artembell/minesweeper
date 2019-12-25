#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../../Config/enums.h"

class CustomWindow {
protected:
	ButtonState leftButtonState, rightButtonState;
	virtual void initResources();
	virtual void checkActions();
public:
	sf::RenderWindow window;

	CustomWindow();
	virtual void render();
};
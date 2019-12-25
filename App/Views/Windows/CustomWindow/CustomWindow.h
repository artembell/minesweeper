#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../../Config/enums.h"

class CustomWindow {
private:
	
	//std::vector<Button> controls;

	//void initButtons();
protected:
	ButtonState leftButtonState, rightButtonState;
	virtual void initResources();
public:

	CustomWindow();
	virtual void render();
	
	sf::RenderWindow window;
};
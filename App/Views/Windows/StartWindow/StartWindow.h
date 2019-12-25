#pragma once

#include <vector>
#include <iostream>
#include "../CustomWindow/CustomWindow.h"
#include "../GameWindow/GameWindow.h"
#include "../../Buttons/Button.h"
#include "../../../Config/enums.h"
#include "../../../Config/constants.h"

class StartWindow {
private:
	sf::RenderWindow window;
	std::vector<Button> m_buttons;
	ButtonState buttonState;
public:
	StartWindow();
	void render();

};
#pragma once
#include "../CustomWindow/CustomWindow.h"
#include "../GameWindow/GameWindow.h"

#include <vector>
#include "../../../../Button.h"
#include "../../../../enums.h"
#include "../../../../constants.h"

class StartWindow {
private:
	sf::RenderWindow window;
	std::vector<Button> m_buttons;
	ButtonState buttonState;
public:
	StartWindow();
	void render();

};
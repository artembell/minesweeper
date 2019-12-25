#pragma once

#include <vector>
#include <iostream>
#include "../CustomWindow/CustomWindow.h"
#include "../GameWindow/GameWindow.h"
#include "../../Buttons/Button.h"
#include "../../../Config/enums.h"
#include "../../../Config/constants.h"

class StartWindow : public CustomWindow {
private:
	std::vector<Button> m_buttons;
	ButtonState buttonState;
	void initResources() override;
public:
	StartWindow();
	void render() override;
	
};
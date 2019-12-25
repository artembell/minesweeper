#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "../CustomWindow/CustomWindow.h"
#include "../GameWindow/GameWindow.h"
#include "../../../Config/enums.h"
#include "../../../Config/constants.h"

class StartWindow : public CustomWindow {
private:
	std::vector<std::string> fileNames;
	std::vector<sf::Vector2i> buttonCoords;
	std::vector<sf::Texture> buttonTextures;
	std::vector<sf::Sprite> buttonSprites;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;

	void initResources() override;
	void checkActions() override;
	int getButtonId(sf::Vector2i position);
public:
	StartWindow();
	void render() override;
};
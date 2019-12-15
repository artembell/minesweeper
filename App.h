#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include <vector>
#include "CustomWindow.h"

class App {

public:
	App();
	void init();

	void OpenGameWindow();
	void OpenStartWindow();
	void OpendRecordsWindow();
private:
	


	//sf::RenderWindow testWindow;

	sf::RenderWindow gameWindow, startWindow, recordsWindow;
	// ----------------------

	Point getCell(int x, int y);
	
	void drawField();
	void drawCell(int i, int j);
	void initResources();
};


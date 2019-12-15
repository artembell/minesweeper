#include "App.h"
#include <string>
#include <iostream>
#include "Button.h"
#include "StartWindow.h"

App::App()
	//window(sf::VideoMode(500, 600), "Minesweeper"),
	//closedCell(sf::RectangleShape(sf::Vector2f(50, 50))),
	//field(10, 10, 20) 
{}

//Point App::getCell(int x, int y)
//{
//	Point point;
//	point.x = (int)(x / cellSize);
//	point.y = (int)(y / cellSize);
//
//	return point;
//}

void App::init() {
	StartWindow testWindow("Welcome to minesweeper!");
	testWindow.render();
}

void App::OpenGameWindow() {
	/*sf::Window gameWindow;*/
	gameWindow.create(sf::VideoMode(500, 500), "Game");



	// create field here with specified size
	

}

void App::OpenStartWindow() {
	//sf::RenderWindow startWindow;
	startWindow.create(sf::VideoMode(500, 500), "Settings");

	/*Button btnBeginner(sf::String("Beginner (10x10 - 10)")),
		btnIntermediate(sf::String("Intermediate (16x16 - 40)")),
		btnExpert(sf::String("Expert (22x22 - 99)"));

	btnBeginner.setPosition(100, 300);
	btnIntermediate.setPosition(100, 360);
	btnExpert.setPosition(100, 420);*/

	while (startWindow.isOpen()) {
		sf::Event event;
		while (startWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				startWindow.close();
		}

		startWindow.clear(sf::Color(255, 255, 200));

		/*btnBeginner.draw(&startWindow);
		btnIntermediate.draw(&startWindow);
		btnExpert.draw(&startWindow);*/

		startWindow.display();
	}
}

void App::OpendRecordsWindow() {
	//sf::Window recordsWindow;
	recordsWindow.create(sf::VideoMode(800, 500), "Records");

	while (recordsWindow.isOpen()) {
		sf::Event event;
		while (recordsWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				recordsWindow.close();
		}
	}
}

void App::drawField() {
	
}

void App::initResources() {
	
}


void App::drawCell(int i, int j) {
	
}


#include "CustomWindow.h"

CustomWindow::CustomWindow() :
	window(sf::VideoMode(500, 500), sf::String("Welcome to minesweeper!"), sf::Style::Close)
{}

void CustomWindow::render() {}
void CustomWindow::initResources() {}
void CustomWindow::checkActions() {}

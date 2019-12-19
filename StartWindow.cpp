#include "StartWindow.h"
#include "Button.h"
#include "GameWindow.h"
#include <iostream>
#include "enums.h"

StartWindow::StartWindow() :
	window(sf::VideoMode(500, 500), sf::String("Welcome to minesweeper!"), sf::Style::Default)
{
	buttonState = RELEASED;
}

void StartWindow::render() {

	// make init() in parent class

	const int BEGINNER = 1, INTERMEDIATE = 2, EXPERT = 3;
	Button btn1(100, 260, "Beginner (10x10, 10 mines)");
	m_buttons.push_back(btn1);
	Button btn2(100, 330, "Intermediate (16x16, 20 mines)");
	m_buttons.push_back(btn2);
	Button btn3(100, 400, "Expert (22x22, 99 mines)");
	m_buttons.push_back(btn3);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ButtonState nowState;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			nowState = PRESSED;
			
			
		}
		else {
			nowState = RELEASED;
			if (buttonState == PRESSED) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				for (int difficulty = 0; difficulty < m_buttons.size(); difficulty++) {
					if (m_buttons.at(difficulty).mouseInShapeBounds(position)) {
						//std::cout << buttonIndex << std::endl;
						window.close();
						GameWindow gameWindow((Difficulty)difficulty);
						gameWindow.render();
						// just create new GameWindow! here
					}
				}
			}
		}

		buttonState = nowState;

		window.clear(sf::Color(255, 255, 200));

		// auto -> in docs
		for (auto button = m_buttons.begin(); button != m_buttons.end(); ++button) {
			button->draw(&window);
		}
		window.display();
	}
}


#include "StartWindow.h"
#include "Button.h"
#include <iostream>

StartWindow::StartWindow(sf::String title) :
	window(sf::VideoMode(500, 500), title) 
{
}

void StartWindow::render() {
	const int BEGINNER = 1, INTERMEDIATE = 2, EXPERT = 3;
	Button btn1(100, 200, "Beginner (10x10, 10 mines)");
	m_buttons.push_back(btn1);
	Button btn2(100, 300, "Intermediate (16x16, 20 mines)");
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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			for (int buttonIndex = 0; buttonIndex < m_buttons.size(); buttonIndex++) {
				if (m_buttons.at(buttonIndex).mouseInShapeBounds(position)) {
					std::cout << buttonIndex << std::endl;
				}
			}
		}

		window.clear(sf::Color(255, 255, 200));
		for (auto button = m_buttons.begin(); button != m_buttons.end(); ++button) {
			button->draw(&window);
		}
		window.display();
	}
}


#include <SFML/Graphics.hpp>
#include <Windows.h>

#include <iostream>

#include "../include/menu.h"
#include "../include/params.h"

using namespace sf;


int main() {

	RenderWindow window(VideoMode(width, height), "ed Tower Defence"/*, Style::Fullscreen*/);
	window.setVerticalSyncEnabled(true);

	Font pixelFont;
	pixelFont.loadFromFile("res/Silkscreen[RUS by Mr.Enot].ttf");

	int stateCode = MENU;

	Vector2i mouse_pos;
	bool mouse_clicked;


	while (window.isOpen()) {

		mouse_pos = Mouse::getPosition(window);
		mouse_clicked = 0;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) stateCode = EXIT;

			if (event.type == Event::KeyPressed) {
				switch (event.key.code)
				{
					case Keyboard::Escape:
						stateCode = EXIT;
						break;
				}
			}
			if (event.type == Event::MouseButtonPressed) {
				switch (event.key.code)
				{
					case Mouse::Left:
						mouse_clicked = 1;
						break;
				}
			}
		}

		std::cout << stateCode << std::endl;
		
		switch (stateCode)
		{
			case MENU:
				stateCode = drawMenu(window, pixelFont ,mouse_pos, mouse_clicked);
				break;

			case CHOICE_LEVEL:
				break;

			case SETTINGS:
				break;

			case GAME:
				break;

			case EXIT:
				window.close();
				break;
		}
	}

	return 0;
}
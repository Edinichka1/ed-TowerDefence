#include "../include/edTowerDefense.h"
#include <Windows.h>
#include <string>


void initButtons(myButton*& menu_buttons, const int window_width, const int window_height, Font& pixel_font, const int screen, const int squarePxSize);
int clickProcessing(Vector2i& mouse_pos, myButton* choice_level_buttons, const int screen, const int level_count);


void edTowerDefense::choiceLevel() {

	static int screen = 0;

	if (!choice_level_buttons || screen_num != screen) {
		delete[] choice_level_buttons;
		initButtons(choice_level_buttons, window_width, window_height, pixel_font, screen, squarePxSize);
		screen = screen_num;
	}

	window.clear(choice_level_background_color);
	for (int i = 30 * screen; i < level_count && i < 30 * screen + 30; ++i) {
		window.draw(choice_level_buttons[i].shape);
		window.draw(choice_level_buttons[i].shapeText);
	}
	window.display();

	if (mouse_clicked) {

		int result = clickProcessing(mouse_pos, choice_level_buttons, screen, level_count);
		if (result != -1) {
			selected_level = result + 1;
			state_code = StateCode::GAME;
			delete[] choice_level_buttons;
		}

		mouse_clicked = 0;
	}
}

void initButtons(myButton*& choice_level_buttons, const int window_width, const int window_height, Font& pixel_font, const int screen, const int squarePxSize) {

	choice_level_buttons = new myButton[30];

	for (int i = 0; i < 30; ++i) {

		choice_level_buttons[i].text = std::to_string(screen * 30 + i + 1);

		choice_level_buttons[i].width = squarePxSize;
		choice_level_buttons[i].height = squarePxSize;

		choice_level_buttons[i].x = window_width / 11 * ((i % 10) + 1) - choice_level_buttons[i].width / 2;
		choice_level_buttons[i].y = window_height / 4 * ((i / 10) + 1) - choice_level_buttons[i].height / 2;

		choice_level_buttons[i].character_size = window_height * 0.07;

		choice_level_buttons[i].color_not_pressed = Color(39, 43, 45);
		choice_level_buttons[i].color_pressed = Color(39, 53, 79);

		choice_level_buttons[i].shape = RectangleShape(Vector2f(choice_level_buttons[i].width, choice_level_buttons[i].height));
		choice_level_buttons[i].shape.setFillColor(choice_level_buttons[i].color_not_pressed);
		choice_level_buttons[i].shape.setPosition(choice_level_buttons[i].x, choice_level_buttons[i].y);

		choice_level_buttons[i].shapeText.setFont(pixel_font);
		choice_level_buttons[i].shapeText.setString(choice_level_buttons[i].text);
		choice_level_buttons[i].shapeText.setCharacterSize(choice_level_buttons[i].character_size);
		choice_level_buttons[i].shapeText.setFillColor(Color::White);
		choice_level_buttons[i].shapeText.setPosition(choice_level_buttons[i].x + choice_level_buttons[i].width / 2
			- choice_level_buttons[i].shapeText.getGlobalBounds().width / 2 - 5, choice_level_buttons[i].y);
	}
}

int clickProcessing(Vector2i& mouse_pos, myButton* choice_level_buttons, const int screen, const int level_count) {
	for (int i = 30 * screen; i < level_count && i < 30 * screen + 30; ++i) {
		if (mouse_pos.x > choice_level_buttons[i].x && mouse_pos.x < choice_level_buttons[i].x + choice_level_buttons[i].width
			&& mouse_pos.y > choice_level_buttons[i].y && mouse_pos.y < choice_level_buttons[i].y + choice_level_buttons[i].height) {
			return i;
		}
	}

	return -1;
}
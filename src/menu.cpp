#include "../include/edTowerDefense.h"


void initButtons(myButton*& menu_buttons, const int window_width, const int window_height, Font& pixel_font);
int clickProcessing(Vector2i& mouse_pos, myButton* menu_buttons);


void edTowerDefense::menu() {

	if (!menu_buttons) {
		initButtons(menu_buttons, window_width, window_height, pixel_font);
	}

	window.clear(menu_background_color);
	for (int i = 0; i < 3; ++i) {
		window.draw(menu_buttons[i].shape);
		window.draw(menu_buttons[i].shapeText);
	}
	window.display();


	if (mouse_clicked) {
		switch (clickProcessing(mouse_pos, menu_buttons)) {
		case 0:
			state_code = StateCode::CHOICE_LEVEL;
			delete[] menu_buttons;
			break;
		case 1:
			state_code = StateCode::SETTINGS;
			delete[] menu_buttons;
			break;
		case 2:
			state_code = StateCode::EXIT;
			delete[] menu_buttons;
			break;
		}
		mouse_clicked = 0;
	}
}


void initButtons(myButton*& menu_buttons, const int window_width, const int window_height, Font& pixel_font) {

	menu_buttons = new myButton[3];

	menu_buttons[0].text = "play";
	menu_buttons[1].text = "settings";
	menu_buttons[2].text = "exit";

	for (int i = 0; i < 3; ++i) {

		menu_buttons[i].width = window_width * 0.6;
		menu_buttons[i].height = window_height * 0.1;

		menu_buttons[i].x = window_width / 2 - menu_buttons[i].width / 2;
		menu_buttons[i].y = (window_height / 4) * (i + 1) - menu_buttons[i].height / 2;

		menu_buttons[i].character_size = window_height * 0.07;

		menu_buttons[i].color_not_pressed = Color(39, 43, 45);
		menu_buttons[i].color_pressed = Color(39, 53, 79);

		menu_buttons[i].shape = RectangleShape(Vector2f(menu_buttons[i].width, menu_buttons[i].height));
		menu_buttons[i].shape.setFillColor(menu_buttons[i].color_not_pressed);
		menu_buttons[i].shape.setPosition(menu_buttons[i].x, menu_buttons[i].y);

		menu_buttons[i].shapeText.setFont(pixel_font);
		menu_buttons[i].shapeText.setString(menu_buttons[i].text);
		menu_buttons[i].shapeText.setCharacterSize(menu_buttons[i].character_size);
		menu_buttons[i].shapeText.setFillColor(Color::White);
		menu_buttons[i].shapeText.setPosition(window_width / 2 - menu_buttons[i].shapeText.getGlobalBounds().width / 2,
			menu_buttons[i].y);
	}
}

int clickProcessing(Vector2i& mouse_pos, myButton* menu_buttons) {

	for (int i = 0; i < 3; ++i) {
		if (mouse_pos.x > menu_buttons[i].x && mouse_pos.x < menu_buttons[i].x + menu_buttons[i].width &&
			mouse_pos.y > menu_buttons[i].y && mouse_pos.y < menu_buttons[i].y + menu_buttons[i].height) {

			return i;
		}
	}

	return -1;
}
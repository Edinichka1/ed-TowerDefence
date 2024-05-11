#include "../include/edTowerDefense.h"
#include <fstream>

void initField(RectangleShape*& field, int selected_level, const int window_width, const int window_height);

void edTowerDefense::playGame() {

	if (!field) {
		initField(field, selected_level, window_width, window_height);
	}

	window.clear(game_background_color);
	for (int i = 0; i < 180; ++i) {
		window.draw(field[i]);
	}
	window.display();
}

Color edTowerDefense::getColor(int color) {
	switch (static_cast<Blocks>(color))
	{
	case Blocks::BEGIN:
		return Color(99, 0, 130);

	case Blocks::BLOCKS:
		return Color(35, 40, 44);

	case Blocks::EMPTY:
		return Color(112, 118, 142);

	case Blocks::ROAD:
		return Color(255, 255, 255);

	case Blocks::END:
		return Color(120, 237, 242);
	}

	return Color(63, 255, 63);
}

void initField(RectangleShape*& field, int selected_level, const int window_width, const int window_height) {
	std::string level_name = "levels/" + std::to_string(selected_level) + ".lvl";
	std::ifstream inf(level_name);

	field = new RectangleShape[180];

	double start_pos_x = (window_width - 70 * 18)/2;
	double start_pos_y = (window_height - 70 * 10)/2;

	for (int i = 0; i < 10; ++i) {

		std::string temp_str;
		std::getline(inf, temp_str);

		start_pos_x = (window_width - 70 * 18) / 2;
		for (int j = 0; j < 18; ++j) {
			field[i * 18 + j] = RectangleShape(Vector2f(70, 70));
			field[i * 18 + j].setFillColor(edTowerDefense::getColor(temp_str[j] - '0'));
			field[i * 18 + j].setPosition(start_pos_x, start_pos_y);
			start_pos_x += 70;
		}
		start_pos_y += 70;
	}
}
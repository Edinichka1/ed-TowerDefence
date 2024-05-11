#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;


struct myButton {

	int width;
	int height;

	int x;
	int y;

	int character_size;
	std::string text;

	Color color_not_pressed;
	Color color_pressed;

	RectangleShape shape;
	Text shapeText;
};

class edTowerDefense {
private:

	RenderWindow window;
	std::string window_title;
	int window_width;
	int window_height;

	Font pixel_font;

	Vector2i mouse_pos;
	bool mouse_clicked;

	enum class StateCode { MENU, SETTINGS, CHOICE_LEVEL, GAME, EXIT };
	StateCode state_code;

	Color menu_background_color = Color(157, 183, 203);
	myButton* menu_buttons = nullptr;

	int level_count;
	int count_level_screen;
	int screen_num;
	const int squarePxSize = 70;
	Color choice_level_background_color = Color(157, 183, 203);
	myButton* choice_level_buttons = nullptr;

	int selected_level;
	enum class Blocks { EMPTY, ROAD, BLOCKS, BEGIN, END };
	Color game_background_color = Color(157, 183, 203);
	RectangleShape* field = nullptr;
	const int widthField = 18;
	const int heightField = 10;

public:
	edTowerDefense(int width, int height, std::string title);
	edTowerDefense() {}
	~edTowerDefense() {}

	void loop();

	void menu();
	//void settings();
	void choiceLevel();
	void playGame();
	static Color getColor(int color);
	//void exit();
};
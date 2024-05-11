#include "../include/edTowerDefense.h"
#include <windows.h>


int getLevelCount();


edTowerDefense::edTowerDefense(int width, int height, std::string title)
	:window_width{ width }, window_height{ height }, window_title{ title }, state_code{ StateCode::MENU }
{
	window.create(VideoMode(window_width, window_height), "ed Tower Defense", Style::Close | Style::Titlebar);

	level_count = getLevelCount() - 1;
	count_level_screen = level_count / 30;
	screen_num = 0;

	// init font
	pixel_font.loadFromFile("res/Silkscreen[RUS by Mr.Enot].ttf");

	// settigns
	window.setVerticalSyncEnabled(true);
	//ContextSettings settings;
	//settings.antialiasingLevel = 8;
}


// default SFML loop
void edTowerDefense::loop() {

	while (window.isOpen()) {

		mouse_pos = Mouse::getPosition(window);
		mouse_clicked = 0;

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) state_code = StateCode::EXIT;

			else if (event.type == Event::KeyPressed) {

				switch (event.key.code)
				{
				case Keyboard::Escape:
					state_code = StateCode::EXIT;
					break;
				}
			}
			else if (event.type == Event::MouseButtonPressed) {

				switch (event.key.code)
				{
				case Mouse::Left:
					mouse_clicked = 1;
					break;
				}
			}
		}

		switch (state_code)
		{
		case StateCode::MENU:
			menu();
			break;

		case StateCode::SETTINGS:
			break;

		case StateCode::CHOICE_LEVEL:
			choiceLevel();
			break;

		case StateCode::GAME:
			playGame();
			break;

		case StateCode::EXIT:
			window.close();
			//exit();
			break;
		}
	}

}



int getLevelCount() {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	int fileCount = 0;

	hFind = FindFirstFile(L"levels/*", &FindFileData);

	do {
		if (hFind == INVALID_HANDLE_VALUE) {
			break;
		}

		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			fileCount++;
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);

	return fileCount;
}

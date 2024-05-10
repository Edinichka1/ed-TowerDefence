#include "../include/menu.h"
#include "../include/params.h"


struct myButton {
	RectangleShape button;
	Text text;

	myButton(RectangleShape& button, Text& text)
		:button{ button }, text{ text } {}
};

myButton* playButtonG = nullptr;
myButton* settingsButtonG = nullptr;
myButton* exitButtonG = nullptr;


const double centerX = width * 0.2;
const double centerY = height * 0.25;
const double down = height * 0.18;
const double widthButton = width * 0.6;
const double heightButton = height * 0.1;
const double characterSize = height * 0.07;

Color buttonColor = Color(39, 43, 45);


bool initButtons = false;

int returnState = MENU;

void initButtonsFunk(Font& pixelFont);
void deInitButtonsFunk();
void drawButtons(RenderWindow& window);
void clickProcessing(RenderWindow& window, Vector2i& mouse_pos);


// draw Window and return codeEvent
int drawMenu(RenderWindow& window, Font& pixelFont, Vector2i& mouse_pos, bool& mouse_clicked) {

	window.clear(Color(157, 183, 203));


	if (!initButtons) {
		initButtonsFunk(pixelFont);
	}
	else if (mouse_clicked) {
		clickProcessing(window, mouse_pos);
		mouse_clicked = 0;
	}


	drawButtons(window);
	window.display();


	if (returnState != MENU) {
		deInitButtonsFunk();
	}

	return returnState;
}


void drawButtons(RenderWindow& window) {
	window.draw(playButtonG->button);
	window.draw(playButtonG->text);

	window.draw(settingsButtonG->button);
	window.draw(settingsButtonG->text);

	window.draw(exitButtonG->button);
	window.draw(exitButtonG->text);
}


void initButtonsFunk(Font& pixelFont) {

	Text playText;
	Text settingsText;
	Text exitText;

	playText.setFont(pixelFont);
	settingsText.setFont(pixelFont);
	exitText.setFont(pixelFont);

	playText.setString("play");
	settingsText.setString("settings");
	exitText.setString("exit");

	playText.setCharacterSize(characterSize);
	settingsText.setCharacterSize(characterSize);
	exitText.setCharacterSize(characterSize);

	playText.setFillColor(Color::White);
	settingsText.setFillColor(Color::White);
	exitText.setFillColor(Color::White);


	RectangleShape playButton(Vector2f(widthButton, heightButton));
	RectangleShape settingsButton(playButton);
	RectangleShape exitButton(playButton);

	playButton.setFillColor(buttonColor);
	settingsButton.setFillColor(buttonColor);
	exitButton.setFillColor(buttonColor);


	playButton.setPosition(centerX, centerY);
	settingsButton.setPosition(centerX, centerY + down);
	exitButton.setPosition(centerX, centerY + down + down);

	playText.setPosition(width / 2 - 1.38 * playText.getCharacterSize(), centerY);
	settingsText.setPosition(width / 2 - 2.5 * settingsText.getCharacterSize(), centerY + down);
	exitText.setPosition(width / 2 - 1.38 * exitText.getCharacterSize(), centerY + down + down);

	playButtonG = new myButton(playButton, playText);
	settingsButtonG = new myButton(settingsButton, settingsText);
	exitButtonG = new myButton(exitButton, exitText);


	initButtons = true;
}

void deInitButtonsFunk() {

	delete playButtonG;
	delete settingsButtonG;
	delete exitButtonG;

	initButtons = false;
}


void clickProcessing(RenderWindow& window, Vector2i& mouse_pos) {

	if (mouse_pos.x > centerX && mouse_pos.x < centerX + widthButton) {

		if (mouse_pos.y > centerY && mouse_pos.y < centerY + heightButton) returnState = CHOICE_LEVEL;

		else if (mouse_pos.y > centerY + down && mouse_pos.y < centerY + heightButton + down) returnState = SETTINGS;

		else if (mouse_pos.y > centerY + down * 2 && mouse_pos.y < centerY + heightButton + down * 2) returnState = EXIT;
	}
}
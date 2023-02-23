#include "menu.h"

menu::menu(float width, float height)
{
	font.loadFromFile("Fonts/Font.ttf");

	Menu[0].setFont(font);
	Menu[0].setFillColor(Color::Red);  
	Menu[0].setString("Play");
	Menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	Menu[1].setFont(font);
	Menu[1].setFillColor(Color::White);
	Menu[1].setString("Option");
	Menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	Menu[2].setFont(font);
	Menu[2].setFillColor(Color::White);
	Menu[2].setString("Exit");
	Menu[2].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

menu::~menu(){}

void menu::draw(RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(Menu[i]);
	}
}

void menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		Menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		Menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void menu::MoveDown()
{
	if (selectedItemIndex + 1 <= MAX_NUMBER_OF_ITEMS)
	{
		Menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		Menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

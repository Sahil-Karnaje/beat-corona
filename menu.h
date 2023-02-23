#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#define MAX_NUMBER_OF_ITEMS 3

class menu
{
public:
	menu(float width, float height);
	~menu();

	void draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem()
	{
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	Font font;
	Text Menu[MAX_NUMBER_OF_ITEMS];

};


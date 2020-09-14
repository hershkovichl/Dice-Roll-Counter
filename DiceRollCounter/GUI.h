#pragma once
#include "Menu.h"


class GUI
{
	sf::RenderWindow& window;
	sf::RectangleShape background;

	static sf::Font font;

	Home homeMenu;
	RollMenu rollMenu;

	Menu* CurrentMenu;
	
	


public:

	void SelectMenu(std::string menu);
	void Draw();
	void leftClick(sf::Vector2i& position);

	GUI(sf::RenderWindow& window);
};


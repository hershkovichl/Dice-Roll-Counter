#pragma once
#include "Menu.h"


class GUI
{
	sf::RenderWindow& window;
	sf::RectangleShape background;


	Home homeMenu;
	RollMenu* rollMenu;

	Menu* CurrentMenu;
	
	


public:
	static sf::Font font;

	void SelectMenu(std::string menu);
	void Draw();
	void leftClick(sf::Vector2i& position);

	GUI(sf::RenderWindow& window);
};


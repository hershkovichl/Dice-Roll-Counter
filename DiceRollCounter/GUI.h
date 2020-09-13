#pragma once

class GUI
{
	sf::RenderWindow& window;
	sf::RectangleShape background;
	static sf::Font font;

	struct Button : public sf::RectangleShape {
		std::string label;

	};

	struct RollButton : public GUI::Button {
		int value;

	};

public:

	GUI(sf::RenderWindow& window);
};


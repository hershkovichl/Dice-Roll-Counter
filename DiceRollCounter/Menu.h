#pragma once

class GUI;

class Menu
{
protected:
	struct Button : public sf::RectangleShape {
		std::string label;
		void (*func_pointer)(std::string);
		std::string argument;
		virtual void Click();

		Button(std::string label);
		Button();
	};


	struct RollButton : public Menu::Button {
		int sideValue;
		virtual void Click(int sides);
	};

public:
	Button HomeButton;


	virtual void Draw(sf::RenderWindow& window) = 0;
	void DrawHomeButton(sf::RenderWindow& window);
	Menu();
};


class Home : public Menu {
	Button diceButtons[7];

public:
	void Draw(sf::RenderWindow& window);
	Home();
};

class RollMenu : public Menu {
	int sides;

public:
	void Draw(sf::RenderWindow& window);
	RollMenu(int sides);
};


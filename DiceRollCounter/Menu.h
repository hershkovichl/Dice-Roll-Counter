#pragma once

class GUI;

class Menu
{
protected:
	struct Button : public sf::RectangleShape {
		std::string label;
		void (*func_pointer)(std::string);
		std::string argument;
		virtual std::string Click();

		sf::Text text;

		Button(std::string label, void (*fptr)(std::string));
		Button(std::string label);
		Button();
	};


	struct RollButton : public Menu::Button {
		int sideValue;
		virtual void Click(int sides);
	};

	void ArrangeMenuButtons(sf::RenderWindow& window, std::vector<Button>& buttons);

public:
	Button HomeButton;

	virtual void leftClick(sf::Vector2i& mousePosition) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	void DrawHomeButton(sf::RenderWindow& window);
	Menu();
};


class Home : public Menu {
	std::vector<Button> diceButtons;

public:
	void ArrangeButtons(sf::RenderWindow& window);

	void leftClick(sf::Vector2i& mousePosition);
	void Draw(sf::RenderWindow& window);
	Home();
};

class RollMenu : public Menu {
	int sides;
	std::vector<RollButton> rollButtons;

public:
	void leftClick(sf::Vector2i& mousePosition);
	void Draw(sf::RenderWindow& window);
	RollMenu(int sides);
};


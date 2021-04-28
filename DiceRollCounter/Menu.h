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
		//virtual void Click(int sides);
		
		RollButton(int side);
		RollButton();
	};

	void ArrangeMenuButtons(sf::RenderWindow& window, std::vector<Button>& buttons);

public:
	Button HomeButton;

	virtual std::string leftClick(sf::Vector2i& mousePosition) = 0;
	virtual void hover(sf::Vector2i& mousePosition) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	void DrawHomeButton(sf::RenderWindow& window);
	Menu();
};


class Home : public Menu {
	std::vector<Button> diceButtons;

public:
	void ArrangeButtons(sf::RenderWindow& window);

	void setFunction(void (*ptr)(std::string));
	std::string leftClick(sf::Vector2i& mousePosition);
	void hover(sf::Vector2i& mouesPosition);
	void Draw(sf::RenderWindow& window);
	Home();
};

class RollMenu : public Menu {
	std::vector<RollButton> rollButtons;
	sf::Sprite diceArt;

public:
	int sides;
	std::string leftClick(sf::Vector2i& mousePosition);
	void hover(sf::Vector2i& mousePosition);
	void Draw(sf::RenderWindow& window);
	RollMenu(int sides);
};


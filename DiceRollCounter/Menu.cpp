#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <string>
#include "Console.h"
#include <iostream>
#include "GUI.h"
using namespace std;

int findClosestSquare(int sides);


void Menu::DrawHomeButton(sf::RenderWindow& window) {
	window.draw(HomeButton);
}

void Menu::ArrangeMenuButtons(sf::RenderWindow& window, vector<Button>& buttons) {
	int width = window.getSize().x;
	int height = window.getSize().y;

	int num = buttons.size();
	
	int cols = findClosestSquare(num);
	int rows = num / cols;

	int buttonWidth = width / cols;
	

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			Button& thisButton = buttons[row + col];
			thisButton.setSize(sf::Vector2f(buttonWidth, buttonWidth));
			thisButton.setPosition(sf::Vector2f(buttonWidth * col, buttonWidth * row + 100.0f));
			thisButton.setFillColor(sf::Color::Blue);
			thisButton.setOutlineColor(sf::Color::Black);
			thisButton.setOutlineThickness(2.0f);
			thisButton.text.setOrigin(sf::Vector2f(thisButton.text.getGlobalBounds().width / 2, thisButton.text.getGlobalBounds().height));
			thisButton.text.setPosition(sf::Vector2f(thisButton.getPosition().x + buttonWidth / 2, thisButton.getPosition().y + buttonWidth / 2));
		}
	}

}

int findClosestSquare(int sides) {// returns biggest dimension
	int large = 1;
	int small;
	for (small = sqrt(sides); small < sides; small++)
		if (sides % small == 0) {
			large = sides / small;
			break;
		}
	if (small > large)
		return small;
	else
		return large;


}

string Menu::Button::Click() {
	if(func_pointer != nullptr)
		func_pointer(argument);

	return label;
}

void Menu::RollButton::Click(int sides) {
	cout << "Roll d" << sides << " sideValue" << endl;
	Console::updateFile(sides, sideValue);
}

Menu::Button::Button(string label, void (*fptr)(std::string)) {
	this->label = label;
	func_pointer = fptr;
	argument = "home";
	

}

Menu::Button::Button(string label) {
	this->label = label;
	func_pointer = nullptr;
	argument = "home";

	text.setFont(GUI::font);
	text.setString(label);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(24);
	
}

Menu::Button::Button() {
	label = "No Label";
	func_pointer = nullptr;
	argument = "home";
}


Menu::Menu() : HomeButton("Main Menu"){
	HomeButton.func_pointer = nullptr;
}

/*===== Home Menu Functions =====*/

void Home::leftClick(sf::Vector2i& mousePosition) {
	for (int i = 0; i < diceButtons.size(); i++)
		if (diceButtons[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			cout << diceButtons[i].label << endl;

}


void Home::Draw(sf::RenderWindow& window) {

	for (int i = 0; i < diceButtons.size(); i++) {
		window.draw(diceButtons[i]);
		window.draw(diceButtons[i].text);
	}

}

Home::Home() : Menu() {
	diceButtons.push_back(Button("d4"));
	diceButtons.push_back(Button("d6"));
	diceButtons.push_back(Button("d8"));
	diceButtons.push_back(Button("d10"));
	diceButtons.push_back(Button("d12"));
	diceButtons.push_back(Button("d20"));
	diceButtons.push_back(Button("d100"));
	
}


void Home::ArrangeButtons(sf::RenderWindow& window) {
	ArrangeMenuButtons(window, diceButtons);
}


/*===== Roll Menu Functions =====*/
void RollMenu::leftClick(sf::Vector2i& mousePosition) {
	cout << "ROLLL" << endl;
}

void RollMenu::Draw(sf::RenderWindow& window) {
	DrawHomeButton(window);

}

RollMenu::RollMenu(int sides){
	this->sides = sides;
}
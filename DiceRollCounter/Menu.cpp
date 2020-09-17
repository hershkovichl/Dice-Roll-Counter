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
	window.draw(HomeButton.text);
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
	//if(func_pointer != nullptr)
		//func_pointer(argument);


	return label;
}

//string Menu::RollButton::Click(int sides) {
	//cout << "Roll d" << sides << " sideValue" << endl;
	//Console::updateFile(sides, sideValue);
//}

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

Menu::RollButton::RollButton(int side) : Menu::Button(to_string(side)){
	sideValue = side;
}
Menu::RollButton::RollButton() : Menu::Button(){
	sideValue = 1;
}


Menu::Menu() : HomeButton("Main Menu"){
	HomeButton.func_pointer = nullptr;
	HomeButton.setSize(sf::Vector2f(200.0f, 95.0f));
	//HomeButton.setPosition(sf::Vector2f(buttonWidth * col, buttonWidth * row + 100.0f));
	HomeButton.setFillColor(sf::Color::Red);
	HomeButton.setOutlineColor(sf::Color::Black);
	HomeButton.setOutlineThickness(2.0f);
	HomeButton.text.setOrigin(sf::Vector2f(HomeButton.text.getGlobalBounds().width / 2, HomeButton.text.getGlobalBounds().height));
	HomeButton.text.setPosition(sf::Vector2f(HomeButton.getPosition().x + HomeButton.getGlobalBounds().width / 2, HomeButton.getPosition().y + HomeButton.getGlobalBounds().height / 2));
}

/*===== Home Menu Functions =====*/

string Home::leftClick(sf::Vector2i& mousePosition) {
	for (int i = 0; i < diceButtons.size(); i++)
		if (diceButtons[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			return diceButtons[i].label;
			//cout << diceButtons[i].label << endl;
	return "null";
}


void Home::Draw(sf::RenderWindow& window) {

	for (int i = 0; i < diceButtons.size(); i++) {
		window.draw(diceButtons[i]);
		window.draw(diceButtons[i].text);
	}

}
void Home::setFunction(void (*ptr)(std::string)) {
	for (int i = 0; i < diceButtons.size(); i++) {
		diceButtons[i].func_pointer = ptr;
		diceButtons[i].argument = diceButtons[i].label;
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
string RollMenu::leftClick(sf::Vector2i& mousePosition) {
	if (HomeButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		return HomeButton.Click();
	
	for (int i = 0; i < rollButtons.size(); i++)
		if (rollButtons[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			return rollButtons[i].Click();
	cout << sides << endl;

	return "null";
}

void RollMenu::Draw(sf::RenderWindow& window) {
	DrawHomeButton(window);
	for (int i = 0; i < rollButtons.size(); i++) {
		window.draw(rollButtons[i]);
		window.draw(rollButtons[i].text);
	}

}

RollMenu::RollMenu(int sides){
	this->sides = sides;
	for (int i = 0, row = 0, col = 0; i < sides; i++, col++) {
		
		if (i > 0 && i % 5 == 0) {
			row++;
			col = 0;
		}
		rollButtons.push_back(RollButton(i + 1));
		RollButton& thisButton = rollButtons[i];
		thisButton.setSize(sf::Vector2f(140, 140));
		thisButton.setPosition(sf::Vector2f(250 + 160* col, 80 + 160 * row));
		thisButton.setFillColor(sf::Color(200,200,200));
		thisButton.text.setOrigin(sf::Vector2f(thisButton.text.getGlobalBounds().width / 2, thisButton.text.getGlobalBounds().height));
		thisButton.text.setPosition(sf::Vector2f(thisButton.getPosition().x + thisButton.getGlobalBounds().width / 2, thisButton.getPosition().y + thisButton.getGlobalBounds().width / 2));
	}

		
}
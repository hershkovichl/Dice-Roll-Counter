#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <string>
#include "Console.h"
#include <iostream>
#include "GUI.h"
using namespace std;


void Menu::DrawHomeButton(sf::RenderWindow& window) {
	window.draw(HomeButton);
}

void Menu::Button::Click() {
	(*func_pointer)(argument);
	
}

void Menu::RollButton::Click(int sides) {
	cout << "Roll d" << sides << " sideValue" << endl;
	Console::updateFile(sides, sideValue);
}

Menu::Button::Button(string label) {
	this->label = label;
	func_pointer = nullptr;
	argument = "home";

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

void Home::Draw(sf::RenderWindow& window) {
	sf::CircleShape circle;
	circle.setRadius(200);
	circle.setFillColor(sf::Color::Green);
	window->draw(circle);

}

Home::Home() : Menu() {
	diceButtons[0] = Button("d4");
	diceButtons[1] = Button("d6");
	diceButtons[2] = Button("d8");
	diceButtons[3] = Button("d10");
	diceButtons[4] = Button("d12");
	diceButtons[5] = Button("d20");
	diceButtons[6] = Button("d100");
}


/*===== Roll Menu Functions =====*/

void RollMenu::Draw(sf::RenderWindow& window) {


}

RollMenu::RollMenu(int sides){
	this->sides = sides;
}
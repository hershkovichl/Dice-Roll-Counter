#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Console.h"
#include "Menu.h"
#include <iostream>

using namespace std;

sf::Font GUI::font;


void GUI::sendRoll(int sides, int roll) {
    cout << "Roll d" << sides << " " << roll << endl;
    Console::updateFile(sides, roll);
}


void GUI::SelectMenu(string menu) {
    if (menu == "Main Menu") {
        CurrentMenu = &homeMenu;
        delete rollMenu;
        rollMenu = nullptr;
    }
    else {
        menu.erase(0, 1);
        if (rollMenu != nullptr)
            delete rollMenu;
        rollMenu = new RollMenu(stoi(menu));

        CurrentMenu = rollMenu;

    }
}


void GUI::Draw() {
    window.draw(background);
    CurrentMenu->Draw(window);
}

void GUI::leftClick(sf::Vector2i& position) {
    string selection = CurrentMenu->leftClick(position);

    if (selection != "null") {
        if (CurrentMenu == &homeMenu || selection == "Main Menu")
            SelectMenu(selection);
        else if (rollMenu != nullptr && CurrentMenu == rollMenu)
            sendRoll(rollMenu ->sides, stoi(selection));

    }
}


GUI::GUI(sf::RenderWindow& _window) : window(_window) {
    background.setFillColor(sf::Color(50, 50, 56));
    background.setSize(sf::Vector2f(window.getSize()));

    if (!font.loadFromFile("arial.ttf"))
        throw invalid_argument("Unable to load font file");

    
    rollMenu = nullptr;
    CurrentMenu = &homeMenu;

    homeMenu.ArrangeButtons(window);

    //rollMenu = new RollMenu(20);
    //CurrentMenu = rollMenu;

}


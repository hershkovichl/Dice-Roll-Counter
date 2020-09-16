#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Console.h"
#include "Menu.h"

using namespace std;

sf::Font GUI::font;

void GUI::SelectMenu(string menu) {
    

}




void GUI::Draw() {
    window.draw(background);
    CurrentMenu->Draw(window);
}

void GUI::leftClick(sf::Vector2i& position) {
    CurrentMenu->leftClick(position);
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


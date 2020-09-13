#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Console.h"

using namespace std;

sf::Font GUI::font;






GUI::GUI(sf::RenderWindow& _window) : window(_window){
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(window.getSize()));

    if (!font.loadFromFile("arial.ttf"))
        throw invalid_argument("Unable to load font file");
}


#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <vector>
#include <iostream>
#include "Random.h"

using namespace std;

int Graph::bar::maxFrequency = 0;
int Graph::bar::numberOfBars = 0;
float Graph::bar::outlineWidth = 2.0f;
int Graph::bar::pixelHeightPerPoint = 50;
sf::Font Graph::font;


void Graph::Draw() {
    window.draw(background);
    DrawBars();
}

void Graph::DrawBars() {
    for (int i = 0; i < bar::numberOfBars; i++) {
        window.draw(Bars[i]);
        if (data->size() <= 20) { // only up to d20 prints bar labels
            window.draw(Bars[i].indexLabel);
            window.draw(Bars[i].frequencyLabel);
        }

    }
}

void Graph::addPoint(int value){
    if (data->size() == 20) { // verifying that dice open is a d20
        data->operator[](value - 1)++;
        Bars[value - 1].frequency++;
        SetBarAesthetics();
    }
}



void Graph::LoadData(vector<int>& _data) {
    this->data = &_data;
}

void Graph::MakeBars() {
    int size = data->size();
    bar::numberOfBars = size;

    for (int i = 0; i < size; i++) {
        Bars.push_back(bar(i, data->at(i)));
        if (data->at(i) > bar::maxFrequency)
            bar::maxFrequency = data->at(i);

    }
    SetBarAesthetics();
}
void Graph::SetBarAesthetics(){
    // setting their positions:
    int width = window.getSize().x;
    int height = window.getSize().y;

    float barwidth = width / bar::numberOfBars;

    ReduceBarHeights();

    for (int i = 0; i < bar::numberOfBars; i++) {
        Bars[i].setSize(sf::Vector2f(barwidth - bar::outlineWidth, Bars[i].frequency * bar::pixelHeightPerPoint));
        Bars[i].setOrigin(sf::Vector2f(0.0f, Bars[i].frequency * bar::pixelHeightPerPoint));
        Bars[i].setPosition(sf::Vector2f(barwidth * i, height));

        Bars[i].setFillColor(sf::Color::Blue);
        Bars[i].setOutlineColor(sf::Color::Black);
        Bars[i].setOutlineThickness(bar::outlineWidth);

        Bars[i].indexLabel.setPosition(sf::Vector2f(barwidth * i + barwidth / 2, height - Bars[i].getSize().y - 15));
        Bars[i].frequencyLabel.setString(to_string(Bars[i].frequency));
        Bars[i].frequencyLabel.setOrigin(sf::Vector2f(Bars[i].frequencyLabel.getGlobalBounds().width / 2, Bars[i].frequencyLabel.getGlobalBounds().height));
        Bars[i].frequencyLabel.setPosition(sf::Vector2f(barwidth * i + barwidth / 2, height - Bars[i].getSize().y + 15));

        
    }

    //SetBarHeights(); // WIP function
}

void Graph::ReduceBarHeights() {

    for(int i = 0; i < bar::numberOfBars; i++)
        if (Bars[i].frequency * bar::pixelHeightPerPoint > MaxBarHeightRatio * window.getSize().y) {
            bar::pixelHeightPerPoint--;
            ReduceBarHeights();
            break;
        }
}


void Graph::SetBarHeights() { // WIP
    int height = window.getSize().y;

    int totalCount = 0;
    for (int i = 0; i < bar::numberOfBars; i++)
        totalCount += Bars[i].frequency;

    float average = totalCount / (float)bar::numberOfBars;


    bool clipHeight = false;
    for (int i = 0; i < bar::numberOfBars; i++)
        if (Bars[i].frequency / average / 3 > MaxBarHeightRatio)
            clipHeight = true;

    for (int i = 0; i < bar::numberOfBars; i++)
        if (clipHeight) {
            Bars[i].setSize(sf::Vector2f(Bars[i].getSize().x, Bars[i].frequency / bar::maxFrequency * MaxBarHeightRatio * height));
        }
        else {
            Bars[i].setSize(sf::Vector2f(Bars[i].getSize().x, Bars[i].frequency / average / 3 * height));
        }
            


    int WindowHeight = window.getSize().y;
    int max = bar::maxFrequency;
    
    //float maxBarHeight = WindowHeight * MaxBar HeightRatio;
    //float fractionalBarHeight = Bar.frequency / max;



}




Graph::Graph(sf::RenderWindow& _window) : window(_window) {
    data = nullptr;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(window.getSize()));
    
    if (!font.loadFromFile("arial.ttf"))
        throw invalid_argument("Unable to load font file");
}

Graph::bar::bar(int _index, int _frequency){
    index = _index;
    frequency = _frequency;

    indexLabel.setFont(font);
    frequencyLabel.setFont(font);

    indexLabel.setString(to_string(index + 1));
    indexLabel.setFillColor(sf::Color::Black);
    indexLabel.setCharacterSize(24);
    indexLabel.setOrigin(sf::Vector2f(indexLabel.getGlobalBounds().width / 2 , indexLabel.getGlobalBounds().height));

    frequencyLabel.setString(to_string(frequency));
    frequencyLabel.setFillColor(sf::Color::White);
    frequencyLabel.setCharacterSize(24);
    frequencyLabel.setOrigin(sf::Vector2f(frequencyLabel.getGlobalBounds().width / 2, frequencyLabel.getGlobalBounds().height));
}
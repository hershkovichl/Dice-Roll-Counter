#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Graph.h" // Class to deal with the histogram
#include "Console.h" // Namespace for all my console-based functions
#include "Random.h"
#include "GUI.h"
#include "Menu.h"

using namespace std;

void SetConfigurations(vector<string> settings);
void Display(vector<int>& data); // This function handles the Graph Window
int AddRandomD20();
void RunConsoleGUI();


bool Settings::debugMode = false;
bool Settings::consoleHistogram = true;
bool Settings::runGUIonStartup = false;


int main() {
	SetConfigurations(Console::readConfigurations());

	// Initial instructions:
	cout << "To input: \"Roll d[dice max] [result]\" \t or \"multi d[dice max]\"" << endl;
	cout << "To get data: \"Data d[dice max]\"" << endl;
	cout << "For visual interface: \"GUI\"" << endl;
	cout << "To undo: \"Undo d[dice max]\" \t or \"Undo d[dice max] [amount]\"" << endl;
	cout << "To exit: \"exit\"" << endl;

	if(Settings::runGUIonStartup)
		RunConsoleGUI();

	vector<string> input;
	while (true) {
		Console::inputStage(input); // Get & Process input

		try {
			//Based on input:
			if (input[0] == "roll")
				Console::Roll(input);
			else if (input[0] == "data") {
				vector<int> data;
				Console::GetData(input, data);
				Display(data);
			}
			else if (input[0] == "exit")
				break;
			else if (input[0] == "multi")
				Console::Multi(input);
			else if (input[0] == "undo")
				Console::Undo(input);
			else if (input[0] == "gui")
				RunConsoleGUI();
			else
				throw invalid_argument("Unknown command");

		}
		// Catching exceptions:
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			continue;
		}
		catch (exception& e) {
			cout << "Other Unkown Error. Error code:" << endl << e.what() << endl;
			continue;
		}
	}
	TextureManager::Clear();
	return 0;
}

void SetConfigurations(vector<string> settings) {
	if (settings[0] == "true")
		Settings::debugMode = true;
	else
		Settings::debugMode = false;

	if (settings[1] == "true")
		Settings::consoleHistogram = true;
	else
		Settings::consoleHistogram = false;

	if (settings[2] == "true")
		Settings::runGUIonStartup = true;
	else
		Settings::runGUIonStartup = false;
}

void RunConsoleGUI() {
	cout << "\nRunning Interactive Controls..." << endl;
	cout << "\tTo proceed in console, close interactive window" << endl;
	sf::RenderWindow guiWindow(sf::VideoMode(1280, 720), "Consle GUI");
	GUI GUI(guiWindow);

	while (guiWindow.isOpen()) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(guiWindow);
		sf::Event event;
		GUI.hover(mousePosition);
		while (guiWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				guiWindow.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left)
					GUI.leftClick(mousePosition);
			}
			else if (event.type == sf::Event::MouseMoved) {
				// GUI.hover moved outside of mouse event bc it is more reliable there
			}

		}
		guiWindow.clear();
		GUI.Draw();
		guiWindow.display();
	}
	cout << "\t...You may proceed:" << endl;
}

void Display(vector<int>& data) {
	cout << "\nGenerating Histogram..." << endl;
	cout << "\tTo proceed in console, close graph window" << endl;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Data Visualization");
	Graph Histogram(window);
	Histogram.LoadData(data);
	Histogram.MakeBars();
	


	bool addtrigger = false;
	int addCount = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/* ===== Debugging Stuff: ===== */
			else if (event.type == sf::Event::MouseButtonPressed) { 
				if (event.mouseButton.button == sf::Mouse::Left && Settings::debugMode && Histogram.GetDataSize() == 20)
					Histogram.addPoint(AddRandomD20());
				else if(event.mouseButton.button == sf::Mouse::Right && Settings::debugMode && Histogram.GetDataSize() == 20)
					addtrigger = true;
			}
		}


		// Debugging to watch histogram rise
		if (addtrigger) {
			Histogram.addPoint(AddRandomD20());
			addCount++;
			if (addCount == 299) {
				addCount = 0;
				addtrigger = false;
			}
		}


		window.clear();
		Histogram.Draw();
		window.display();
	}
	cout << "\t...You may proceed:" << endl;
}


int AddRandomD20(){
	int randomInt = Random::Int(1, 20);

	vector<string> rand;
	rand.push_back("roll");
	rand.push_back("d20");	   
	rand.push_back(to_string(randomInt));

	cout << randomInt << endl;

	Console::Roll(rand);
	return randomInt;
}




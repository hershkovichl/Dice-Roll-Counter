#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.h" // Class to deal with the histogram
#include "Console.h" // Namespace for all my console-based functions
#include "Random.h"
#include "GUI.h"

using namespace std;

void SetConfigurations(vector<string> settings);
void Display(vector<int>& data); // This function handles the Graph Window
int AddRandomD20();
void findClosestSquare(int sides);

struct Settings {
	static bool debugMode; // in debug mode: left click on histogram to add 1 random roll, right click to add 300. ONLY works on d20
};
bool Settings::debugMode = false;

int main() {
	SetConfigurations(Console::readConfigurations());


	// Initial instructions:
	cout << "To input: \"Roll d[dice max] [result]\" \t or \"multi d[dice max]\"" << endl;
	cout << "To get data: \"Data d[dice max]\"" << endl;
	cout << "To exit: \"exit\"" << endl;


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
			else
				cout << "Hi" << endl;

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
	return 0;
}

void SetConfigurations(vector<string> settings) {
	if (settings[0] == "true")
		Settings::debugMode = true;
	else
		Settings::debugMode = false;
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


void findClosestSquare(int sides) {
	int large;
	for (int small = sqrt(sides); small < sides; small++) 
		if (sides % small == 0) {
			large = sides / small;
			break;
		}
			

}

#include <iostream>
#include "Console.h"
#include <fstream>
#include <exception>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;
struct Settings;


vector<string> Console::readConfigurations() {
	string filename = (string)"configurations" + (string)".txt";
	
	vector<string> defaultSettings;
	defaultSettings.push_back("Debug_Mode: false");
	defaultSettings.push_back("Print_Console_Histogram: true");
	defaultSettings.push_back("Auto_Start_GUI: false");
	
	//Read phase:
	vector<string> lines;

	
	fstream file(filename);
	string line;
	if (file.good()) {
		ifstream infile(filename, fstream::in);
		 while(getline(infile, line)) {
			lines.push_back(line);
		}
		infile.close();
		if (lines.size() != defaultSettings.size()) { // if missing some settings, take the default ones
			for (int i = lines.size(); i < defaultSettings.size(); i++)
				lines.push_back(defaultSettings[i]);
			ofstream outfile(filename, fstream::out);
			for (int i = 0; i < lines.size(); i++) {
				outfile << lines[i] << endl;
			}
		}
	}
	else { // if file doesn't exist, take default settings and Write it
		lines = defaultSettings;
		
		ofstream outfile(filename, fstream::out);
		for (int i = 0; i < lines.size(); i++) {
			outfile << lines[i] << endl;
		}
	}

	//Edit phase:

	for (int i = 0; i < lines.size(); i++) {
		string str;
		istringstream lineStream(lines[i]);
		getline(lineStream, str, ' '); // Get rid of setting name. Ex: deletes "Debug-Mode: "
		getline(lineStream, str, ' ');
		lines[i] = str;
	}

	// Make everything lowercase:
	for (int index = 0; index < lines.size(); index++)
		for (int i = 0; i < lines[index].size(); i++)
			lines[index].at(i) = tolower(lines[index].at(i));

	return lines;
}




void Console::inputStage(vector<string>& input) {
	input.clear();
	string str;
	getline(cin, str);

	istringstream inStream(str);

	while (getline(inStream, str, ' ')) {
		input.push_back(str);
	}

	for (int index = 0; index < input.size(); index++)
		for (int i = 0; i < input[index].size(); i++)
			input[index].at(i) = tolower(input[index].at(i));
}
void Console::Roll(vector<string>& input) {
	if (input.size() != 3)
		throw invalid_argument("Bad input. Format example:\n Roll d20 12");
	int rollValue;

	if (input[1] == "d20") {
		// Syntax that makes sense:
		rollValue = verifyRoll(20, input[2]);
		updateFile(20, rollValue);
		// The rest are in a simplified syntax:
	}
	else if (input[1] == "d100")
		updateFile(100, verifyRoll(100, input[2]));
	else if (input[1] == "d12")
		updateFile(12, verifyRoll(12, input[2]));
	else if (input[1] == "d8")
		updateFile(8, verifyRoll(8, input[2]));
	else if (input[1] == "d6")
		updateFile(6, verifyRoll(6, input[2]));
	else if (input[1] == "d4")
		updateFile(4, verifyRoll(4, input[2]));
	else
		throw invalid_argument("Invalid Die.\nValid Dice include d100, d20, d8, d6, d4");

}
void Console::Multi(std::vector<std::string>& input) {
	if (input.size() != 2)
		throw invalid_argument("Bad input. Format example:\n\tMulti d20\n\t12\n\t7\n\t20\n\tetc...");
	
	if (input[1] == "d20" || "d100" || "d12" || "d8" || "d6" || "d4") {
		input[1].erase(0, 1);
		int sides = stoi(input[1]);

		cout << "Enter values to add to d" << input[1] << ". Type \"done\" once finished" << endl;
		string line;
		cout << "\t";
		getline(cin, line);
		cout << "\t";
		while (line != "done") {
			try {
				int rollValue = verifyRoll(sides, line);
				updateFile(sides, rollValue);

			}
			catch (invalid_argument& e) {
				cout << e.what() << endl;
			}
			cout << "\t";
			getline(cin, line);
			cout << "\t";
		}
		cout << "Multi roll done..." << endl;
	}
	else
		throw invalid_argument("Invalid Die.\nValid Dice include d100, d20, d8, d6, d4\nExample: multi d20");
}

int Console::verifyRoll(int max, string& input) {
		int rollvalue = stoi(input);

		if (rollvalue > max || rollvalue < 1)
			throw invalid_argument("Roll value outside of possible bounds");

		return rollvalue;
}

void Console::updateFile(int max, int rollValue) {
	string filename = (string)"d" + to_string(max) + (string)".dat";

	vector<int> lines;


	//Read phase:
	fstream file(filename);
	string line;
	if (file.good()) {
		ifstream infile(filename, fstream::in);
		for (int i = 0; i < max; i++) {
			getline(infile, line);
			lines.push_back(stoi(line));
		}
		infile.close();
	}
	else
		for (int i = 0; i < max; i++)
			lines.push_back(0);

	//Edit phase:
	lines[rollValue - 1]++;
	cout << "Total rolls of " << rollValue << ": " << lines[rollValue - 1] << endl;
	//Write phase:
	ofstream outfile(filename, fstream::out);
	for (int i = 0; i < lines.size(); i++) {
		outfile << lines[i] << endl;
	}

}

void Console::GetData(vector<string>& input, vector<int>& lines) {
	if (input.size() > 3 || input.size() < 2)
		throw invalid_argument("Bad input. Format example:\n Data d20  ==or== Data d20 visual");
	int rollValue;


	if (input[1] == "d20")
		ReadData(20, lines);
	else if (input[1] == "d100")
		ReadData(100, lines);
	else if (input[1] == "d12")
		ReadData(12, lines);
	else if (input[1] == "d8")
		ReadData(8, lines);
	else if (input[1] == "d6")
		ReadData(6, lines);
	else if (input[1] == "d4")
		ReadData(4, lines);
	else
		throw invalid_argument("Invalid Die.\nValid Dice include d100, d20, d8, d6, d4");
}

void Console::ReadData(int diceMax, vector<int>& lines) {
	string filename = (string)"d" + to_string(diceMax) + (string)".dat";
	//Read phase:
	fstream file(filename);
	string line;
	if (file.good()) {
		ifstream infile(filename, fstream::in);
		for (int i = 0; i < diceMax; i++) {
			getline(infile, line);
			lines.push_back(stoi(line));
		}
		infile.close();
	}
	else
		throw invalid_argument("No data with this die available");


	printTable("Total Rolls", "Face", "Number of Rolls", diceMax, lines);
	cout << endl << endl << "Histogram:" << endl;
	if(Settings::consoleHistogram)
		printHist(diceMax, lines);
}

void Console::printTable(string title, string header1, string header2, int diceMax, vector<int> intVec) {
	// Instructions:
	// Output the information in a formatted table. The title is right justified with a setw() value of 33. 
	// Column 1 has a setw() value of 20. Column 2 has a setw() value of 23. (3 pts)

	int total = 0;
	for (int i = 0; i < intVec.size(); i++)
		total += intVec[i];
	

	cout << endl << setw(20) << right << title << endl;
	cout << setw(14) << left << header1 << "|" << setw(17) << right << header2 << endl;
	cout << "--------------------------------";
	for (int i = 0; i < intVec.size(); i++)
		cout << endl << setw(14) << left << i + 1 << "|" << setw(17) << right << intVec[i];
		cout << endl << setw(14) << left << "Total" << "|" << setw(17) << right << total;

}

void Console::printHist(int diceMax, vector<int> intVec) {
	//Instructions: 
	//Output the information as a formatted histogram. 
	// Each name is right justified with a setw() value of 20. (4 pts)
	for (int i = 0; i < intVec.size(); i++) {
		cout << setw(5) << right << i + 1 << " ";
		for (int j = 0; j < intVec[i]; j++)
			cout << "*";
		cout << endl;
	}
}

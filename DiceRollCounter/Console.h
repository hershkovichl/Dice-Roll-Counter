#pragma once
#include <vector>
#include <string>


struct Settings {
	static bool debugMode; // in debug mode: left click on histogram to add 1 random roll, right click to add 300. ONLY works on d20
	static bool consoleHistogram;
	static bool runGUIonStartup;
};


namespace Console{
	std::vector<std::string> readConfigurations();
	void inputStage(std::vector<std::string>& input);
	void Roll(std::vector<std::string>& input);
	void Multi(std::vector<std::string>& input);
	int verifyRoll(int max, std::string& input);
	void updateFile(int max, int rollValue);
	void GetData(std::vector<std::string>& input, std::vector<int>& data);
	void ReadData(int diceMax, std::vector<int>& lines);
	void printTable(std::string title, std::string header1, std::string header2, int diceMax, std::vector<int> intVec);
	void printHist(int diceMax, std::vector<int> intVec);
};


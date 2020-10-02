#pragma once
#include <vector>
#include <string>
#include <map>

class Bin
{
	int sides;
	std::map<int, int> rolls;

	
public: 
	void read(int sides);
	void updateFile(int max, int rollValue);
	void write();
};


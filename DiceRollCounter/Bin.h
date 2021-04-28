#pragma once
#include <vector>
#include <string>
#include <map>

/*
class Bin
{
	int sides;
	std::map<int, int> rolls;

	
public: 
	void read(int sides);
	void updateFile(int max, int rollValue);
	void write();
};
*/

struct BinSettings {
	static int capacity;
};

namespace Bin{
	void updateBin(int max, int rollValue);
	void undo(int max, int amount, std::vector<int>& sides);


}
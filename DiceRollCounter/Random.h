#pragma once
#include <random>
class Random
{
	// One instance of the x variable, and all instances of this class SHARE this variable
	// static variables/functions exist for the lifetime of yo8ur program
	static std::mt19937 random;

public:
	static int x;
	// one and only one of this function
	static int Int(int min, int max);
	static float Float(float min, float max);


};


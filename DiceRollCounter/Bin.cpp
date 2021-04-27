#include <iostream>
#include "Bin.h"
#include <fstream>
#include <exception>
#include <sstream>
#include <vector>

using namespace std;
int BinSettings::capacity = 1000;

void Bin::updateBin(int max, int rollValue) {
	string filename = (string)"d" + to_string(max) + (string)".bin";
	char byte = rollValue; // Cast roll value into a char so that it's 1 byte


	fstream file(filename);
	long size = 0;
	char* buffer = NULL;
	if (file.good()) {
		ifstream infile(filename, fstream::in || ios_base::binary);
		// Get size of file
		infile.seekg(0, infile.end);
		size = infile.tellg();
		// if the file is at capacity, pop the first value
		if (size >= BinSettings::capacity) {
			infile.seekg(1);
			size--;
		}
		else
			infile.seekg(0);
		
		// allocate memory on heap for current state of file
		buffer = new char[size];
		// read the file onto the buffer
		infile.read(buffer, size);
	}

	ofstream outfile(filename, ios_base::binary);
	if (outfile.is_open()) {
		if (size > 0) {
			outfile.write(buffer, size);
			delete[] buffer;
		}
		outfile.write((char*)&byte, sizeof(byte));
	}
}
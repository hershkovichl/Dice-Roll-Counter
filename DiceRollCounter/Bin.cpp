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
	int size = 0;
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
			// return the buffer to the bin file
			outfile.write(buffer, size);
			delete[] buffer;
		}
		// add the new roll to the bin file
		outfile.write((char*)&byte, sizeof(byte));
	}
}


void Bin::undo(int max, int undoAmount, std::vector<int>& sides) {
	string filename = (string)"d" + to_string(max) + (string)".bin";
	
	fstream file(filename);
	if (file.good()) {
		ifstream infile(filename, ios_base::binary);
		infile.seekg(0, infile.end);
		int size = infile.tellg();
		if (size == 0)
			throw length_error("No Dice Data To Undo");
		if (undoAmount > size)
			throw invalid_argument("Invalid. The maximum you can undo for this die is: " + to_string(size));
		

		char byte;
		// push the last [undoAmount] rolls from .bin file to vector
		for (int i = 0; i < undoAmount; i++) {
			infile.seekg(size - i - 1);
			infile.read(&byte, sizeof(byte));
			int roll = byte;
			cout << "Undone Roll: " << roll << endl;
			sides.push_back(roll);
		}

		// save the non-undone rolls to a buffer
		infile.seekg(0);
		char* buffer = new char[size - undoAmount];
		infile.read(buffer, size - undoAmount);

		// save the buffer back to the .bin
		ofstream outfile(filename, ios_base::binary);
		outfile.write(buffer, size - undoAmount);
		delete[] buffer;
	}
	else
		throw invalid_argument("No file found for this die");
}
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "LSystemLoader.h"

LSystemLoader::LSystemLoader(const char *lSystemFilePath)
{
	// Read all lines of the file
	ExtractLinesFromFile(lSystemFilePath, &this->lSystemFileStrings);
}

LSystemLoader::~LSystemLoader()
{
}

std::vector<std::string> LSystemLoader::GetLSystemDefinition()
{
	return this->lSystemFileStrings;
}

void LSystemLoader::ExtractLinesFromFile(const char * file, std::vector<std::string>* lineStringVector)
{
	// Create input stream to the l-system file
	std::ifstream inputFile(file, std::ios::in);

	// Check if there were any problems opening or creating an input stream to the file
	if (!inputFile.is_open() || inputFile.bad())
	{
		std::cout << "File was not opened properly!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// String to store a line of the file
	std::string line;
	// Read until the end of the file
	while (!inputFile.eof())
	{
		// Read in a line from the input buffer
		std::getline(inputFile, line);
		// Place the line of the file into vector that was passed in
		lineStringVector->push_back(line);
	}

	// Close the input stream
	inputFile.close();
}

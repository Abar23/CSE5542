#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "LSystemLoader.h"

LSystemLoader::LSystemLoader(const char *lSystemFilePath)
{
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
	std::ifstream inputFile(file, std::ios::in);

	if (!inputFile.is_open() || inputFile.bad())
	{
		std::cout << "File was not opened properly!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);
		lineStringVector->push_back(line);
	}

	inputFile.close();
}

#ifndef LSYSTEMLOADER_H
#define LSYSTEMLOADER_H

#include <vector>

class LSystemLoader
{
public:
	LSystemLoader(const char *lSystemFilePath);

	~LSystemLoader();

	std::vector<std::string> GetLSystemDefinition();
		 
private:
	std::vector<std::string> lSystemFileStrings;

	static void ExtractLinesFromFile(const char *file, std::vector<std::string> *lineStringVector);
};

#endif // !LSYSTEMLOADER_H


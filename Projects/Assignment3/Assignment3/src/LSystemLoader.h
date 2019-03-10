#ifndef LSYSTEMLOADER_H
#define LSYSTEMLOADER_H

#include <vector>

class LSystemLoader
{
public:
	/**
	 * Create l-system loader
	 * @param lSystemFilePath
	 *		String that holds the file path to the defined l-system
	 */
	LSystemLoader(const char *lSystemFilePath);

	~LSystemLoader();

	/**
	 * Returns the file as a vector of strings where each string is a line from the file
	 */
	std::vector<std::string> GetLSystemDefinition();
		 
private:
	std::vector<std::string> lSystemFileStrings;

	/**
	 * Reads in each line of the file and stores them in the lineStringVector pointer that was 
	 * passed in
	 * @param file
	 *		String that holds the file path to the defined l-system
	 * @param lineStringVector
	 *		Pointer to the vector that will store lines of the file
	 */
	static void ExtractLinesFromFile(const char *file, std::vector<std::string> *lineStringVector);
};

#endif // !LSYSTEMLOADER_H


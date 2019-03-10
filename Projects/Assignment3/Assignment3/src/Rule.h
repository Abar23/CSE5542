#ifndef RULE_H
#define RULE_H

#include <vector>
#include <unordered_map>

class Rule
{
public:
	/**
	 * Create rule object that wil store and expand the sentence of the l-system based upon
	 * the expansion rules that have been defined in the file
	 * @param lSystemDefinition
	 *		vector that stores the strings of the l-system definition file
	 */
	Rule(std::vector<std::string> *lSystemDefinition);
	
	~Rule();

	/**
	 * Expand the current sentence of the l-system based upon the expansion rules
	 */
	void Expand();

	/**
	 * Returns the curent sentence of the l-system
	 */
	std::string GetSentence();

private:
	std::unordered_map<std::string, std::string> ruleMap;
	std::string sentence;
};

#endif // RULE_H
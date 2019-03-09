#ifndef RULE_H
#define RULE_H

#include <vector>
#include <unordered_map>

class Rule
{
public:
	Rule(std::vector<std::string> *lSystemDefinition);
	
	~Rule();

	void Expand();

	std::string GetSentence();

private:
	std::unordered_map<std::string, std::string> ruleMap;
	std::string initiator;
	std::string sentence;
};

#endif // RULE_H
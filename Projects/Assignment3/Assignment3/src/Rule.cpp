#include "Rule.h"

#define INITIAl_SENTENCE_POS 4
#define RULES_POS 5

Rule::Rule(std::vector<std::string> *lSystemDefinition) 
{
	// Store the inital position 
	this->sentence = lSystemDefinition->at(INITIAl_SENTENCE_POS);

	// Extract rules from passed in string vector
	for (unsigned int i = RULES_POS; i < lSystemDefinition->size(); i++)
	{
		std::string rule = lSystemDefinition->at(i);
		this->ruleMap.insert(std::pair<std::string, std::string>(rule.substr(0, 1), rule.substr(2)));
	}
}

Rule::~Rule()
{
}

void Rule::Expand()
{
	// Create empty string that will be used to construct the new sentence from the expansion rules
	std::string newSentence("");
	// Iterate over the current sentence
	for (unsigned int i = 0; i < this->sentence.length(); i++)
	{
		// Extract character from the sentence as a string
		std::string character(1, this->sentence.at(i));
		// Check if the extracted character has an expansion rule
		if (this->ruleMap.find(character) != this->ruleMap.end())
		{
			newSentence += this->ruleMap.at(character);
		}
		else
		{
			newSentence += character;
		}
	}

	// Update the current sentence to the newly expanded sentence
	this->sentence = newSentence;
}

std::string Rule::GetSentence()
{
	return this->sentence;
}

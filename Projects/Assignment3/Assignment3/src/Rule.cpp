#include "Rule.h"

Rule::Rule(std::vector<std::string> *lSystemDefinition) 
{
	this->initiator = lSystemDefinition->at(4);
	this->sentence = this->initiator;

	for (unsigned int i = 5; i < lSystemDefinition->size(); i++)
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
	std::string newSentence("");
	for (unsigned int i = 0; i < this->sentence.length(); i++)
	{
		std::string character(1, this->sentence.at(i));
		if (this->ruleMap.find(character) != this->ruleMap.end())
		{
			newSentence += this->ruleMap.at(character);
		}
		else
		{
			newSentence += character;
		}
	}

	this->sentence = newSentence;
}

std::string Rule::GetSentence()
{
	return this->sentence;
}

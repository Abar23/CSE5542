#define GLM_ENABLE_EXPERIMENTAL
#include <stack>
#include <ctype.h>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "TurtleGraphics.h"

TurtleGraphics::TurtleGraphics(std::vector<std::string> *lSystemDefinition)
{
	this->numberOfExpansions = std::atoi(lSystemDefinition->at(0).c_str());
	this->angle = std::atof(lSystemDefinition->at(1).c_str());
	this->length = std::atof(lSystemDefinition->at(2).c_str());
	this->rule = new Rule(lSystemDefinition);

	for (unsigned int i = 0; i < this->numberOfExpansions; i++)
	{
		this->rule->Expand();
		this->length *= 0.5f;
	}
}

TurtleGraphics::~TurtleGraphics()
{
	delete this->rule;

	for(unsigned int i = 0; i < this->lSystemComponents.size(); i++)
	{
		delete this->lSystemComponents.at(i);
	}
}

void TurtleGraphics::ConstructLSystem()
{
	stack<std::pair<glm::vec2, float>> turtleStack;
	
	float currentAngle = 0.0f;
	glm::vec2 turtlePoint = glm::vec2(0.0f, 0.0f);

	std::string sentence = this->rule->GetSentence();
	for (unsigned int i = 0; i < sentence.length(); i++)
	{
		char sentenceCharacter = sentence[i];
		
		if (isalpha(sentenceCharacter))
		{
			if (sentenceCharacter != 'X' || sentenceCharacter != 'Y')
			{
				float originalXPosOfTurtle = turtlePoint.x;
				float originalYPosOfTurtle = turtlePoint.y;
				turtlePoint.x += this->length * sinf(glm::radians(currentAngle));
				turtlePoint.y += this->length * cosf(glm::radians(currentAngle));
				Cylinder *lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				lSystemCylinder->PlaceCylinderBetweenPoints(glm::vec3(originalXPosOfTurtle, originalYPosOfTurtle, 0.0f), glm::vec3(turtlePoint.x, turtlePoint.y, 0.0f), currentAngle);
				this->lSystemComponents.push_back(lSystemCylinder);
			}
		}
		else if (sentenceCharacter == '+')
		{
			currentAngle += this->angle;
		}
		else if (sentenceCharacter == '-')
		{
			currentAngle -= this->angle;
		}
		else if (sentenceCharacter == '[')
		{
			turtleStack.push(std::make_pair(turtlePoint, currentAngle));
		}
		else if (sentenceCharacter == ']')
		{
			std::pair<glm::vec2, float> pair = turtleStack.top();
			currentAngle = pair.second;
			turtlePoint = pair.first;
			turtleStack.pop();
		}
	}
}

void TurtleGraphics::Draw(bool wireFrame, Shader *shader)
{
	for (unsigned int i = 0; i < this->lSystemComponents.size(); i++)
	{
		shader->SetUniformMatrix4fv("model", &this->lSystemComponents.at(i)->GetModelMatrix());
		this->lSystemComponents.at(i)->Draw(wireFrame);
	}
}

#define GLM_ENABLE_EXPERIMENTAL
#include <stack>
#include <ctype.h>
#include <cmath>
#include <ctime>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "TurtleGraphics.h"

#define NUM_EXPANSIONS_POS 0
#define ANGLE_POS 1
#define LENGTH_POS 2
#define RANDOMNESS_POS 3

#define BROWN glm::vec3(0.54f, 0.27f, 0.07f)
#define ORANGE glm::vec3(0.83f, 0.35f, 0.07f)
#define YELLOW glm::vec3(0.95f, 0.73f, 0.18f)
#define GREEN glm::vec3(0.0f, 1.0f, 0.0f)

TurtleGraphics::TurtleGraphics(std::vector<std::string> *lSystemDefinition)
{
	this->numberOfExpansions = std::atoi(lSystemDefinition->at(NUM_EXPANSIONS_POS).c_str());
	this->angle = std::atof(lSystemDefinition->at(ANGLE_POS).c_str());
	this->length = std::atof(lSystemDefinition->at(LENGTH_POS).c_str());
	
	this->rule = new Rule(lSystemDefinition);
	for (unsigned int i = 0; i < this->numberOfExpansions; i++)
	{
		this->rule->Expand();
		this->length *= 0.5f;
	}

	if (lSystemDefinition->at(RANDOMNESS_POS).compare("true") == 0)
	{
		this->isRandom = true;
		srand(time(0));
	}
	else
	{
		this->isRandom = false;
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
	float currentLength = this->length;
	float lengthOffset = this->length / 2.0f;
	glm::vec2 turtlePoint = glm::vec2(0.0f, 0.0f);

	std::string sentence = this->rule->GetSentence();
	for (unsigned int i = 0; i < sentence.length(); i++)
	{
		char sentenceCharacter = sentence[i];
		
		if (isalpha(sentenceCharacter))
		{
			if ((sentenceCharacter != 'X' && sentenceCharacter != 'Z') && isupper(sentenceCharacter))
			{
				float originalXPosOfTurtle = turtlePoint.x;
				float originalYPosOfTurtle = turtlePoint.y;

				if (this->isRandom)
				{
					currentLength = this->length + (fmod(std::rand(), this->length) - lengthOffset);
				}

				turtlePoint.x += currentLength * sinf(glm::radians(currentAngle));
				turtlePoint.y += currentLength * cosf(glm::radians(currentAngle));

				Cylinder *lSystemCylinder;
				if (sentenceCharacter == 'B')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), BROWN);
				}
				else if (sentenceCharacter == 'O')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), ORANGE);
				}
				else if (sentenceCharacter == 'Y')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), YELLOW);

				}
				else
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), GREEN);
				}
				lSystemCylinder->PlaceCylinderBetweenPoints(glm::vec3(originalXPosOfTurtle, originalYPosOfTurtle, 0.0f), glm::vec3(turtlePoint.x, turtlePoint.y, 0.0f), currentAngle);
				this->lSystemComponents.push_back(lSystemCylinder);
			}
			else
			{
				if (sentenceCharacter == 'b')
				{
					turtlePoint.x -= this->length * sinf(glm::radians(currentAngle));
					turtlePoint.y -= this->length * cosf(glm::radians(currentAngle));
				}
			}
		}
		else if (sentenceCharacter == '+')
		{
			if (this->isRandom)
			{
				currentAngle += fmod(std::rand(), this->angle);
			}
			else
			{
				currentAngle += this->angle;
			}
		}
		else if (sentenceCharacter == '-')
		{
			if (this->isRandom)
			{
				currentAngle -= fmod(std::rand(), this->angle);
			}
			else
			{
				currentAngle -= this->angle;
			}
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

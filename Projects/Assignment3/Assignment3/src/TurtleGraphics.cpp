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

// Defines for the colors used in the l-system
#define BROWN glm::vec3(0.54f, 0.27f, 0.07f)
#define ORANGE glm::vec3(0.83f, 0.35f, 0.07f)
#define YELLOW glm::vec3(0.95f, 0.73f, 0.18f)
#define GREEN glm::vec3(0.0f, 1.0f, 0.0f)

TurtleGraphics::TurtleGraphics(std::vector<std::string> *lSystemDefinition)
{
	// Extract the number of generations for the l-system
	this->numberOfExpansions = std::atoi(lSystemDefinition->at(NUM_EXPANSIONS_POS).c_str());
	// Extract the angle from the l-system
	this->angle = std::atof(lSystemDefinition->at(ANGLE_POS).c_str());
	// Extract the branch/twig length
	this->length = std::atof(lSystemDefinition->at(LENGTH_POS).c_str());
	
	// Create rule object that can store and expand the sentence for he l-system
	this->rule = new Rule(lSystemDefinition);
	// Iterate for the number of expansions
	for (unsigned int i = 0; i < this->numberOfExpansions; i++)
	{
		// Expand the sentence of l-system
		this->rule->Expand();
		// Reduce the length of the branch/twigs based upon the expansions
		this->length *= 0.7f; // 70% reduction as mentioned on the website
	}

	// Check if the l-system is stochastic/random
	if (lSystemDefinition->at(RANDOMNESS_POS).compare("true") == 0)
	{
		this->isRandom = true;
		// Set random seed for future random calls
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

	// Delete all cylinders stored in the lSystemsComponents vector
	for(unsigned int i = 0; i < this->lSystemComponents.size(); i++)
	{
		delete this->lSystemComponents.at(i);
	}
}

void TurtleGraphics::ConstructLSystem()
{
	// Create stack that will save and restore the states of the turtle
	stack<std::pair<glm::vec2, float>> turtleStack;
	
	// Set length to the initial length
	float currentLength = this->length;
	// Create length offset that will be used in random calls if the system is stochastic
	float lengthOffset = this->length / 2.0f;

	// Set angle to 0 degrees
	float currentAngle = 0.0f;
	// Set initial position of the turtle to the origin of the xy-plane
	glm::vec2 turtlePoint = glm::vec2(0.0f, 0.0f);

	// Retrieve the sentence stored in rule object
	std::string sentence = this->rule->GetSentence();
	// Iterate over the sentence to construct the l-system
	for (unsigned int i = 0; i < sentence.length(); i++)
	{
		// Get character from the l-System
		char sentenceCharacter = sentence[i];
		
		// Check if the character is a letter
		if (isalpha(sentenceCharacter))
		{
			// Move turtle forward except if the character is X or Z and is capitalized
			if ((sentenceCharacter != 'X' && sentenceCharacter != 'Z') && isupper(sentenceCharacter))
			{
				// Save original position of the turtle
				float originalXPosOfTurtle = turtlePoint.x;
				float originalYPosOfTurtle = turtlePoint.y;

				// Check if the l-system is stochastic
				if (this->isRandom)
				{
					// Update the current length to be between the inital length of the l-system plus or minus the length offset
					currentLength = this->length + (fmod(std::rand(), this->length) - lengthOffset);
				}

				// Move the turtle to the next position
				turtlePoint.x += currentLength * sinf(glm::radians(currentAngle));
				turtlePoint.y += currentLength * cosf(glm::radians(currentAngle));

				// Set cylinder pointer that will be created after evaluating the current character
				Cylinder *lSystemCylinder;
				// Create blue cylinder for B
				if (sentenceCharacter == 'B')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), BROWN);
				}
				// Create orange cylinder for O
				else if (sentenceCharacter == 'O')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), ORANGE);
				}
				// Create yellow cylinder for Y
				else if (sentenceCharacter == 'Y')
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), YELLOW);
				}
				// Create green cylinder for all other characters
				else
				{
					lSystemCylinder = new Cylinder(8, 8, glm::vec3(0.0f, 0.0f, 0.0f), GREEN);
				}
				// set the cylinder to be between the original and new positin of the turtle
				lSystemCylinder->PlaceCylinderBetweenPoints(glm::vec3(originalXPosOfTurtle, originalYPosOfTurtle, 0.0f), glm::vec3(turtlePoint.x, turtlePoint.y, 0.0f), currentAngle);
				// Add the new cylinder in to the vector that will store all components of the l-system
				this->lSystemComponents.push_back(lSystemCylinder);
			}
			// Character is lowercase letter
			else
			{
				// Move backwards without drawing
				if (sentenceCharacter == 'b')
				{
					turtlePoint.x -= this->length * sinf(glm::radians(currentAngle));
					turtlePoint.y -= this->length * cosf(glm::radians(currentAngle));
				}
			}
		}
		// Increment the current angle by the angle defined in the l-system
		else if (sentenceCharacter == '+')
		{
			// Check if l-system is stochastic
			if (this->isRandom)
			{
				// Add to the current angle a number between 0 and the angle of the l-system
				currentAngle += fmod(std::rand(), this->angle);
			}
			else
			{
				currentAngle += this->angle;
			}
		}
		// Decrement the current angle by the angle defined in the l-system
		else if (sentenceCharacter == '-')
		{
			// Check if l-system is stochastic
			if (this->isRandom)
			{
				// Subtract from the current angle a number between 0 and the angle of the l-system
				currentAngle -= fmod(std::rand(), this->angle);
			}
			else
			{
				currentAngle -= this->angle;
			}
		}
		// Save the current state of the turtle
		else if (sentenceCharacter == '[')
		{
			turtleStack.push(std::make_pair(turtlePoint, currentAngle));
		}
		// Restore the prior state of the turtle
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
	// Draw each of the cylinders in the lSystemsComponents vector
	for (unsigned int i = 0; i < this->lSystemComponents.size(); i++)
	{
		shader->SetUniformMatrix4fv("model", &this->lSystemComponents.at(i)->GetModelMatrix());
		this->lSystemComponents.at(i)->Draw(wireFrame);
	}
}

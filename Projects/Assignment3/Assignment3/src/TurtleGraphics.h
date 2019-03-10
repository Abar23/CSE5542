#ifndef TURTLEGRAPHICS_H
#define TURTLEGRAPHICS_H

#include <vector>
#include "Cylinder.h"
#include "Rule.h"
#include "Shader.h"

class TurtleGraphics
{
public:
	TurtleGraphics(std::vector<std::string> *lSystemDefinition);
	
	~TurtleGraphics();

	void ConstructLSystem();

	void Draw(bool wireFrame, Shader *shader);

private:
	float length;
	float angle;
	int numberOfExpansions;
	bool isRandom;
	std::vector<Cylinder *> lSystemComponents;
	Rule *rule;
};

#endif // TURTLEGRAPHICS_H

#ifndef TURTLEGRAPHICS_H
#define TURTLEGRAPHICS_H

#include <vector>
#include "Cylinder.h"
#include "Rule.h"
#include "Shader.h"

class TurtleGraphics
{
public:
	/**
	 * Creates "turtle" that is able to create and draw the l-system defined in the file
	 * @param lSystemDefinition
	 *		vector that stores the strings of the l-system definition file
	 */
	TurtleGraphics(std::vector<std::string> *lSystemDefinition);
	
	~TurtleGraphics();

	/**
	 * Create components of the l-system. The components are 3D cylinder primitives
	 */
	void ConstructLSystem();

	/**
	 * Draws the components that comprise the l-system
	 * @param wireFrame
	 *		A boolean that determines whether the shape is drawn as a wire frame
	 *		or filled. True for wire fram and false for fill.
	 * @param shader
	 *		Pointer to the active shader
	 */
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

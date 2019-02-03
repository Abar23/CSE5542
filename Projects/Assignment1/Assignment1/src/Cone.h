#ifndef CONE_H
#define CONE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Cone : public Shape
{
public:
	/**
	 * Creates a cone primitive
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 * @param position
	 *		The initial position of the object
	 * @param color
	 *		The color of the object
	 */
	Cone(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);

	~Cone();

private:
	/**
	 * Calculates all vertices needed for the geometry of the cone base
	 * upon the number of stacks and sectors
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 * @param color
	 *		The color of the object
	 */
	static std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	/**
	 * Calculates all indices needed for the geometry of the cone base
	 * upon the number of stacks and sectors
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 */
	static std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //CONE_H
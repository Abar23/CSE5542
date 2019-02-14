#ifndef TORUS_H
#define TORUS_H

#include <vector>
#include "Shape.h"
#include "Mesh.h"

class Torus : public Shape
{
public:
	/**
	 * Creates a torus primitive
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 * @param position
	 *		The initial position of the object
	 * @param color
	 *		The color of the object
	 */
	Torus(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);
	
	~Torus();

private:
	/**
	 * Calculates all vertices needed for the geometry of the torus
	 * upon the number of stacks and sectors
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 * @param color
	 *		The color of the object
	 */
	std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	/**
	 * Calculates all indices needed for the geometry of the torus
	 * upon the number of stacks and sectors
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 */
	std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //TORUS_H
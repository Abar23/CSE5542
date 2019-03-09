#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Sphere : public Shape
{
public:
	/**
	 * Creates a sphere primitive
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 * @param position
	 *		The initial position of the object
	 * @param color
	 *		The color of the object
	 */
	Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);
	
	~Sphere();

private:
	/**
	 * Calculates all vertices needed for the geometry of the sphere
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
	 * Calculates all indices needed for the geometry of the spjere
	 * upon the number of stacks and sectors
	 * @param stacks
	 *		Number of stacks to divide the object
	 * @param sectors
	 *		Number of sectors to divide the object
	 */
	static std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //SPHERE_H
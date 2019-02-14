#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Plane : public Shape
{
public:
	/**
	 * Creates a plane primitive
	 * @param heightSubdivision
	 *		Number of subdivisions along the height of the plane
	 * @param widthSubdivision
	 *		Number of subdivisions along the width of the plane
	 * @param position
	 *		The initial position of the object
	 * @param color
	 *		The color of the object
	 */
	Plane(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 position, glm::vec3 color);
	
	~Plane();

private:
	/**
	 * Calculates all vertices needed for the geometry of the plane
	 * upon the number of stacks and sectors
	 * @param heightSubdivision
	 *		Number of subdivisions along the height of the plane
	 * @param widthSubdivision
	 *		Number of subdivisions along the width of the plane
	 * @param color
	 *		The color of the object
	 */
	static std::vector<MeshVertex> SetVertices(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 *color);

	/**
	 * Calculates all indices needed for the geometry of the plane
	 * upon the number of stacks and sectors
	 * @param heightSubdivision
	 *		Number of subdivisions along the height of the plane
	 * @param widthSubdivision
	 *		Number of subdivisions along the width of the plane
	 */
	static std::vector<unsigned int> SetIndices(unsigned int heightSubdivision, unsigned int widthSubdivision);
};

#endif
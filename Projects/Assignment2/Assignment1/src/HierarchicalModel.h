#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include "ModelNode.h"
#include "Shader.h"

class HierarchicalModel
{
public:
	/**
	 * Stores the root node of ModelNode structures
	 * @para root
	 *		The root of ModelNode structures
	 */
	HierarchicalModel(ModelNode *rootNode);

	~HierarchicalModel();

	/**
	 * Returns root of the hierachy
	 */
	ModelNode * GetRootNode();

	/**
	 * Draws each component of the hierarchy
	 * @param wireFrame
	 *		A boolean that determines whether the shape is drawn as a wire frame
	 *		or filled. True for wire fram and false for fill.
	 * @para shader
	 *		Pointer to the shader that is to be used to render all components of 
	 *		the hierarchy
	 */
	void Draw(bool wireFrame, Shader *shader);

private:
	ModelNode *rootNode;
};

#endif //HIERARCHICALMODEL_H
#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include "ModelNode.h"
#include "Shader.h"

class HierarchicalModel
{
public:
	HierarchicalModel(ModelNode *rootNode);

	~HierarchicalModel();

	ModelNode * GetRootNode();

	void Draw(bool wireFrame, Shader *shader);

private:
	ModelNode *rootNode;
};

#endif //HIERARCHICALMODEL_H
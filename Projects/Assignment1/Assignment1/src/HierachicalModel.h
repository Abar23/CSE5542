#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include "ModelNode.h"
#include "Shader.h"

class HierachicalModel
{
public:
	HierachicalModel(ModelNode *rootNode);

	~HierachicalModel();

	ModelNode * GetRootNode();

	void Draw(bool wireFrame, Shader *shader);

private:
	ModelNode *rootNode;
};

#endif //HIERARCHICALMODEL_H
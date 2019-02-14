#include <stack>
#include "HierarchicalModel.h"

HierarchicalModel::HierarchicalModel(ModelNode *rootNode)
{
	this->rootNode = rootNode;
}

HierarchicalModel::~HierarchicalModel()
{
	// Use DFS to delete all nodes that comprise the hierachy
	stack<ModelNode *> nodeStack;
	nodeStack.push(this->rootNode);

	while (!nodeStack.empty())
	{
		ModelNode *node = nodeStack.top();
		nodeStack.pop();

		for (int i = 0; i < node->NumberOfChildren(); i++)
		{
			nodeStack.push(node->GetChildAt(i));
		}

		delete node;
	}
}

ModelNode * HierarchicalModel::GetRootNode()
{
	return this->rootNode;
}

void HierarchicalModel::Draw(bool wireFrame, Shader *shader)
{
	//Use DFS to draw all nodes in the hierchy
	stack<ModelNode *> nodeStack;
	nodeStack.push(this->rootNode);

	while (!nodeStack.empty())
	{
		ModelNode *node = nodeStack.top();
		// Use shader pointer to set the model matrix of the ModelNode to the uniform of the shader
		shader->SetUniformMatrix4fv("model", &node->GetShape()->GetModelMatrix());
		node->GetShape()->Draw(wireFrame);
		nodeStack.pop();

		for (int i = 0; i < node->NumberOfChildren(); i++)
		{
			nodeStack.push(node->GetChildAt(i));
		}
	}
}

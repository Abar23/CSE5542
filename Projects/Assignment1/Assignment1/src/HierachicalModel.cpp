#include <stack>
#include "HierachicalModel.h"

HierachicalModel::HierachicalModel(ModelNode *rootNode)
{
	this->rootNode = rootNode;
}

HierachicalModel::~HierachicalModel()
{
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

ModelNode * HierachicalModel::GetRootNode()
{
	return this->rootNode;
}

void HierachicalModel::Draw(bool wireFrame, Shader *shader)
{
	stack<ModelNode *> nodeStack;
	nodeStack.push(this->rootNode);

	while (!nodeStack.empty())
	{
		ModelNode *node = nodeStack.top();
		shader->SetUniformMatrix4fv("model", &node->GetShape()->GetModelMatrix());
		node->GetShape()->Draw(wireFrame);
		nodeStack.pop();

		for (int i = 0; i < node->NumberOfChildren(); i++)
		{
			nodeStack.push(node->GetChildAt(i));
		}
	}
}

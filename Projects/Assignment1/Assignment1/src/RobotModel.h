#ifndef ROBOTMODEL_H

#include "ModelNode.h"
#include "HierarchicalModel.h"
#include "Shader.h"

class RobotModel
{
public:
	RobotModel(Shader *shader);

	~RobotModel();

	void Draw();

	void Update();

private:
	HierarchicalModel *hierarchy;
	Shader *shader;
};

#endif //ROBOTMODEL_H
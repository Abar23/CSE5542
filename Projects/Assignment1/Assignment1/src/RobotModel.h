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

	static void UpdateAppendage(unsigned int childIndexOfModel, unsigned int numberOfComponents, ModelNode *body, glm::mat4 *transform);
};

#endif //ROBOTMODEL_H
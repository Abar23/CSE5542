#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "ModelNode.h"
#include "HierarchicalModel.h"
#include "Shader.h"

class RobotModel
{
public:
	/**
	 * Creates the robot model
	 * @param shader
	 *		Pointer to the robots shader program
	 */
	RobotModel(Shader *shader);

	~RobotModel();

	/**
	 * Draws the shape
	 * @param wireFrame
	 *		A boolean that determines whether the shape is drawn as a wire frame
	 *		or filled. True for wire fram and false for fill.
	 */
	void Draw(bool wireFrame);

	/**
	 * Applies tranformations to all objects that comprise the robot
	 */
	void Update();

private:
	HierarchicalModel *hierarchy;
	Shader *shader;

	/**
	 * Apply transforms to each component that comrpise one of the appendages of the robot
	 * @param wireFrame
	 *		A boolean that determines whether the shape is drawn as a wire frame
	 *		or filled. True for wire fram and false for fill.
	 */
	static void UpdateAppendage(unsigned int childIndexOfModel, unsigned int numberOfComponents, ModelNode *body, glm::mat4 *transform);
};

#endif //ROBOTMODEL_H
#include <stack>
#include "GLM\glm.hpp"
#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Shape.h"
#include "Torus.h"
#include "RobotModel.h"

#define LEFT_LEG_CHILD_INDEX 0
#define RIGHT_LEG_CHILD_INDEX 1
#define HEAD_CHILD_INDEX 2
#define LEFT_ARM_CHILD_INDEX 3
#define RIGHT_ARM_CHILD_INDEX 4

#define NUM_ARM_COMPONENTS 4
#define NUM_LEG_COMPONENTS 5
#define NUM_HEAD_COMPONENTS 2

RobotModel::RobotModel(Shader *shader)
{
	//Body
	Shape *body = new Cube(6, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	ModelNode *root = new ModelNode(body, glm::vec3(0.0f, 6.50f, 0.0f), glm::vec3(3.0f, 3.25f, 1.75f));

	//Head
	Shape *head = new Sphere(36, 18, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	Shape *halo = new Torus(24, 24, glm::vec3(0.0f), glm::vec3(1.0f, 0.84f, 0.0f));
	ModelNode *headNode = new ModelNode(head, glm::vec3(0.0f, 2.6f, 0.0f), glm::vec3(2.0f));
	ModelNode *haloNode = new ModelNode(halo, glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(3.0f, 2.0f, 3.0f), glm::vec3(1.0f, 0.0f, 0.0f), -20.0f);

	//Right leg
	Shape *leftLegTopJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *leftLegTopSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *leftLegBottomJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *leftLegBottomSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *leftFoot = new Cone(16, 16, glm::vec3(0.0f), glm::vec3(0.73f, 0.33f, 0.83f));
	ModelNode *leftLegTopJointNode = new ModelNode(leftLegTopJoint, glm::vec3(-1.0f, -2.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *leftLegTopSegmentNode = new ModelNode(leftLegTopSegment, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.5f, 1.50f, 0.5f));
	ModelNode *leftLegBottomJointNode = new ModelNode(leftLegBottomJoint, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *leftLegBottomSegmentNode = new ModelNode(leftLegBottomSegment, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.5f, 1.50f, 0.5f));
	ModelNode *leftFootNode = new ModelNode(leftFoot, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.25f, 1.0f, 1.25f));

	//Left leg
	Shape *rightLegTopJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *rightLegTopSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *rightLegBottomJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *rightLegBottomSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *rightFoot = new Cone(16, 16, glm::vec3(0.0f), glm::vec3(0.73f, 0.33f, 0.83f));
	ModelNode *rightLegTopJointNode = new ModelNode(rightLegTopJoint, glm::vec3(1.0f, -2.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *rightLegTopSegmentNode = new ModelNode(rightLegTopSegment, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.5f, 1.50f, 0.5f));
	ModelNode *rightLegBottomJointNode = new ModelNode(rightLegBottomJoint, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *rightLegBottomSegmentNode = new ModelNode(rightLegBottomSegment, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.5f, 1.50f, 0.5f));
	ModelNode *rightFootNode = new ModelNode(rightFoot, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.25f, 1.0f, 1.25f));

	//Left Arm
	Shape *leftArmShoulderJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *leftArmTopSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *leftArmElbowJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *leftArmBottomSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	ModelNode *leftArmShoulderJointNode = new ModelNode(leftArmShoulderJoint, glm::vec3(-1.75f, 1.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *leftArmTopSegmentNode = new ModelNode(leftArmTopSegment, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.75f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);
	ModelNode *leftArmElbowJointNode = new ModelNode(leftArmElbowJoint, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *leftArmBottomSegmentNode = new ModelNode(leftArmBottomSegment, glm::vec3(-0.9f, 0.0f, 0.0f), glm::vec3(0.5f, 1.75f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);

	//Right Arm
	Shape *rightArmShoulderJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *rightArmTopSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	Shape *rightArmElbowJoint = new Sphere(12, 6, glm::vec3(0.0f), glm::vec3(0.93f, 0.46f, 0.0f));
	Shape *rightArmBottomSegment = new Cylinder(8, 8, glm::vec3(0.0f), glm::vec3(0.27f, 0.5f, 0.7f));
	ModelNode *rightArmShoulderJointNode = new ModelNode(rightArmShoulderJoint, glm::vec3(1.75f, 1.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *rightArmTopSegmentNode = new ModelNode(rightArmTopSegment, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.75f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);
	ModelNode *rightArmElbowJointNode = new ModelNode(rightArmElbowJoint, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(.75f, .75f, .75f));
	ModelNode *rightArmBottomSegmentNode = new ModelNode(rightArmBottomSegment, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 1.75f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);

	// Add left leg to hierarchy
	root->AddChildNode(leftLegTopJointNode);
	leftLegTopJointNode->AddChildNode(leftLegTopSegmentNode);
	leftLegTopSegmentNode->AddChildNode(leftLegBottomJointNode);
	leftLegBottomJointNode->AddChildNode(leftLegBottomSegmentNode);
	leftLegBottomSegmentNode->AddChildNode(leftFootNode);

	// Add right leg to hierarchy
	root->AddChildNode(rightLegTopJointNode);
	rightLegTopJointNode->AddChildNode(rightLegTopSegmentNode);
	rightLegTopSegmentNode->AddChildNode(rightLegBottomJointNode);
	rightLegBottomJointNode->AddChildNode(rightLegBottomSegmentNode);
	rightLegBottomSegmentNode->AddChildNode(rightFootNode);

	// Add head
	root->AddChildNode(headNode);
	headNode->AddChildNode(haloNode);

	// Add left arm to hierarchy
	root->AddChildNode(leftArmShoulderJointNode);
	leftArmShoulderJointNode->AddChildNode(leftArmTopSegmentNode);
	leftArmTopSegmentNode->AddChildNode(leftArmElbowJointNode);
	leftArmElbowJointNode->AddChildNode(leftArmBottomSegmentNode);

	// Add right arm to hierarchy
	root->AddChildNode(rightArmShoulderJointNode);
	rightArmShoulderJointNode->AddChildNode(rightArmTopSegmentNode);
	rightArmTopSegmentNode->AddChildNode(rightArmElbowJointNode);
	rightArmElbowJointNode->AddChildNode(rightArmBottomSegmentNode);

	this->hierarchy = new HierarchicalModel(root);
	this->shader = shader;
}

RobotModel::~RobotModel()
{
	delete this->hierarchy;
}

void RobotModel::Draw(bool wireFrame)
{
	this->hierarchy->Draw(wireFrame, this->shader);
}

void RobotModel::Update()
{
	glm::mat4 transform = glm::mat4(1.0f);
	stack<glm::mat4> matrixStack;
	ModelNode *body = this->hierarchy->GetRootNode();

	transform = body->UpdateModelMatrix(&transform);

	matrixStack.push(transform);
	UpdateAppendage(LEFT_LEG_CHILD_INDEX, NUM_LEG_COMPONENTS, body, &transform);
	transform = matrixStack.top();
	matrixStack.pop();

	matrixStack.push(transform);
	UpdateAppendage(RIGHT_LEG_CHILD_INDEX, NUM_LEG_COMPONENTS, body, &transform);
	transform = matrixStack.top();
	matrixStack.pop();

	matrixStack.push(transform);
	UpdateAppendage(HEAD_CHILD_INDEX, NUM_HEAD_COMPONENTS, body, &transform);
	transform = matrixStack.top();
	matrixStack.pop();

	matrixStack.push(transform);
	UpdateAppendage(LEFT_ARM_CHILD_INDEX, NUM_ARM_COMPONENTS, body, &transform);
	transform = matrixStack.top();
	matrixStack.pop();

	matrixStack.push(transform);
	UpdateAppendage(RIGHT_ARM_CHILD_INDEX, NUM_ARM_COMPONENTS, body, &transform);
	transform = matrixStack.top();
	matrixStack.pop();
}

void RobotModel::UpdateAppendage(unsigned int childIndexOfModel, unsigned int numberOfComponents, ModelNode *body, glm::mat4 *transform)
{
	ModelNode *node = body->GetChildAt(childIndexOfModel);
	for (unsigned int i = 0; i < numberOfComponents; i++)
	{
		*transform = node->UpdateModelMatrix(transform);
		if (i != numberOfComponents - 1)
		{
			node = node->GetChildAt(0);
		}
	}
}

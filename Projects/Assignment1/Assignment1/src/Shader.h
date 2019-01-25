#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include "GLM\glm.hpp"
#include "GL\glew.h"

using namespace std;

class Shader
{
public:
	Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

	~Shader();

	void UseProgram();

	void TurnOffProgram();

	GLuint GetProgramID();

	void SetUniformMatrix4fv(const char *uniformName, glm::mat4 *matrix);

private:
	GLuint programID;
};

#endif //SHADER_H
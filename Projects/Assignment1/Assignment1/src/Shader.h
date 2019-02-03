#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include "GLM\glm.hpp"
#include "GL\glew.h"

using namespace std;

class Shader
{
public:
	/**
	 * Creates a shader program in the OpenGL rendering pipeline
	 * @param vertexShaderPath
	 *		File path to the vertex shader
	 * @param fragmentShaderPath
	 *		File path to the fragment shader
	 */
	Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

	~Shader();

	/**
	 * Sets shader program as the current renderer
	 */
	void BindProgram();

	/**
	 * Unbinds shader program from rendering pipeline
	 */
	void UnbindProgram();

	/**
	 * Returns shader program ID
	 */
	GLuint GetProgramID();

	/**
	 * Sets 4x4 matrix to a uniform matrix in the shader program
	 * @param uniformName
	 *		Name of the uniform present in the shader program
	 * @param matrix	
	 *		Pointer to the matrix that will set the uniform value
	 */
	void SetUniformMatrix4fv(const char *uniformName, glm::mat4 *matrix);

private:
	GLuint programID;

	static void CheckForShaderCompilationErrors(std::string type, unsigned int shader);
};

#endif //SHADER_H
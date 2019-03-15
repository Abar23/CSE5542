#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include "Shader.h"

static char* ReadShaderSource(const char *shaderPath)
{
	//open file and make it read only
	char *content;
	FILE *shaderCode = fopen(shaderPath, "r");
	if (shaderCode != NULL)
	{
		//move file pointer to the end of the file and determine the length of the file
		fseek(shaderCode, 0, SEEK_END);
		long fileLength = ftell(shaderCode);
		fseek(shaderCode, 0, SEEK_SET);
		//Create char pointer that will point to the text content of the shader
		content = (char *)calloc(fileLength + 1, sizeof(char));
		if (content != NULL)
		{
			//Read the file
			fread(content, 1, fileLength, shaderCode);
			//Denote end of the string with null character
			content[fileLength + 1] = '\0';
		}
		else
		{
			printf("Error ocurred while reading shader file!");
			exit(EXIT_FAILURE);
		}
		fclose(shaderCode);
	}
	else
	{
		std::cout << "Shader \"" << shaderPath << "\" does not exist!" << std::endl;
		exit(EXIT_FAILURE);
	}
	return content;
}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	//Create and compile vertex shader
	const char *vertexShaderCode = ReadShaderSource(vertexShaderPath);
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);
	CheckForShaderCompilationErrors("VERTEX", vertexShaderID);

	//Create and compile fragment shader
	const char *fragmentShaderCode = ReadShaderSource(fragmentShaderPath);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderID);
	CheckForShaderCompilationErrors("FRAGMENT", fragmentShaderID);

	//Create shader program and link each shader to the program
	this->programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	CheckForShaderCompilationErrors("PROGRAM", vertexShaderID);

	// Remove shader source from GPU
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	// Delete compiled shader binary
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
	glDeleteProgram(this->programID);
}

void Shader::BindProgram()
{
	glUseProgram(this->programID);
}

void Shader::UnbindProgram()
{
	glUseProgram(0);
}

GLuint Shader::GetProgramID()
{
	return this->programID;
}

void Shader::SetUniformMatrix4fv(const char *uniformName, glm::mat4 *matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, uniformName), 1, GL_FALSE, (GLfloat *)&matrix[0][0]);
}

void Shader::SetUniformToTextureUnit(const char *uniformName, uint8_t textureUnit)
{
	assert(textureUnit >= 0 && textureUnit <= 31);

	glUniform1i(glGetUniformLocation(this->programID, uniformName), GL_TEXTURE0 + textureUnit);
}

void Shader::CheckForShaderCompilationErrors(std::string type, unsigned int shader)
{
	int successStatus;
	char errorLog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &successStatus);
		if (!successStatus)
		{
			glGetProgramInfoLog(shader, 1024, NULL, errorLog);
			std::cout << "Program Linking Error of type: " << type << "\n" << errorLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &successStatus);
		if (!successStatus)
		{
			glGetShaderInfoLog(shader, 1024, NULL, errorLog);
			std::cout << "Shader Compilation Error of type: " << type << "\n" << errorLog << std::endl;
		}
	}
}

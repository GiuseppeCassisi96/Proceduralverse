#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <GLM/include/gtc/type_ptr.hpp>
#include <fstream>
#define GLEW_STATIC
#include <GLEW/Include/GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void DeleteShaders();
	void DeleteProgram();
	void UseProgram();
	void SetUniformMatrix4(const char* uniformParamName, glm::mat4& value);
private:
	unsigned int program;
	unsigned int vertexObj, fragmentObj;
	std::stringstream vertexStream, fragmentStream;
	std::string vertexShaderCode, fragmentShaderCode;
	void CompileShader(const char* shaderName, unsigned int &shaderObj,
		unsigned int shaderType);
};

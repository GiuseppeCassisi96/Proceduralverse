#pragma once
#include <sstream>
#include <string>
#include <GLM/include/glm.hpp>
#include <iostream>
#include <fstream>
#include <GLEW/Include/GL/glew.h>
#include <GLM/include/gtc/matrix_transform.hpp>
#include <GLM/include/gtc/type_ptr.hpp>

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

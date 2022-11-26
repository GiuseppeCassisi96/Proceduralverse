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
	Shader(const char* vertexShaderPath, const char* tcsShaderPath, const char* tesShaderPath, const char* fragmentShaderPath);
	void DeleteShaders();
	void DeleteProgram();
	void UseProgram();
	void SetUniformMatrix4(const char* uniformParamName, glm::mat4& value);
	void SetUniformFloat(const char* uniformParamName, float value);
	void SetUniformInt(const char* uniformParamName, int value);
private:
	unsigned int program;
	unsigned int vertexObj, fragmentObj, tcsObj, tesObj;
	std::stringstream vertexStream, fragmentStream, tcsStream, tesStream;
	std::string vertexShaderCode, fragmentShaderCode, tcsShaderCode, tesShaderCode;
	void CompileShader(const char* shaderName, unsigned int &shaderObj,
		unsigned int shaderType);
};

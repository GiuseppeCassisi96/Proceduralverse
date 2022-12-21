#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <GLM/include/gtc/type_ptr.hpp>
#include <fstream>
#define GLEW_STATIC
#include <vector>
#include <GLEW/Include/GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	Shader(const char* computeShaderPath);
	void DeleteShaders();
	void DeleteProgram();
	void UseProgram();
	void SetUniformMatrix4(const char* uniformParamName, glm::mat4& value);
	void SetUniformMatrix3(const char* uniformParamName, glm::mat3& value);
	void SetUniformFloat(const char* uniformParamName, float value);
	void SetUniformInt(const char* uniformParamName, int value);
	void SetSubroutine(const char* functionName, GLenum shaderType);
	void DispatchCompute();
private:
	unsigned int program;
	unsigned int vertexObj, fragmentObj, computeObj;
	std::stringstream vertexStream, fragmentStream, computeStream;
	std::string vertexShaderCode, fragmentShaderCode, computeShaderCode;
	void CompileShader(const char* shaderName, unsigned int &shaderObj,
		unsigned int shaderType);
};

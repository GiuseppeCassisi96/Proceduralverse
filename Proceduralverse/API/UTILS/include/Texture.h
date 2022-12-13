#pragma once
#include <iostream>
#define GLEW_STATIC
#include <vector>
#include <GLEW/Include/GL/glew.h>
#include <STB_IMAGE/Include/stb_image.h>
#include "UTILS/include/Constants.h"
#include "Shader.h"

class Texture
{
public:
	//Texture file 
	Texture(const char* fileName);
	//Empty texture
	Texture(GLenum textureEnum);
	Texture(GLenum textureEnum, std::vector<float> HeightMap);
	std::vector<float> GetValuesOfMap();
	void UseTexture(Shader& shader, GLenum textureNum);
	int width, height;
	unsigned int textureID;
};

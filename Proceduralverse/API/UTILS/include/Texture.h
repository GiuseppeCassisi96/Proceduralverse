#pragma once
#include <iostream>
#define GLEW_STATIC
#include <vector>
#include <GLEW/Include/GL/glew.h>
#include <STB_IMAGE/Include/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* fileName);
	int width, height;
};

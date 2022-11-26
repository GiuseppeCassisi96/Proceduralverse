#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GLEW/Include/GL/glew.h>
#include <STB_IMAGE/Include/stb_image.h>
class Texture
{
public:
	Texture(const char* fileName);
	int width, height;
};

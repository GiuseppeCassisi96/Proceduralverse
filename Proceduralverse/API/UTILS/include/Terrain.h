#pragma once
#define GLEW_STATIC
#include <vector>
#include <GLM/include/vec2.hpp>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <GLEW/Include/GL/glew.h>

class Terrain
{


public:
	struct TerrainVertex
	{
		glm::vec3 Position;
		glm::vec2 UVCoord;
	};
	Terrain(int meshRes);
	void DrawTerrain();
	int meshResolution;
private:
	void SetupTerrain();
	unsigned int VAO, VBO, EBO;
	unsigned int XDim, YDim;
	std::vector<TerrainVertex> vertices;
	std::vector<unsigned int> indices;
};


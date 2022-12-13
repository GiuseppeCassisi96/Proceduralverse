#pragma once
#define GLEW_STATIC
#include <vector>
#include <GLM/include/vec2.hpp>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <GLEW/Include/GL/glew.h>
#include <GLM/include/fwd.hpp>
#include "Shader.h"
#include "Texture.h"
#include "UTILS/include/Model.h"
#include "UTILS/include/Constants.h"
class Terrain
{


public:
	struct TerrainVertex
	{
		glm::vec3 Position;
		glm::vec2 UVCoord;
	};
	Terrain(std::vector<float> heightMap);
	void DrawTerrain(glm::mat4& terrainModel, glm::mat4& cameraView, Shader& terrainShader, int subroutineIndex, std::vector<float>
	                 heightMap, Texture& texture);
	std::vector<TerrainVertex> GetTerrainVertices();
	
private:
	void SetupTerrain();
	unsigned int VAO, VBO, EBO;
	std::vector<unsigned int> indices;
	std::vector<TerrainVertex> vertices;
	std::vector<float> heightMap;
};


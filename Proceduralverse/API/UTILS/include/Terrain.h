#pragma once
#define GLEW_STATIC
#include <vector>
#include <GLM/include/vec2.hpp>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <GLEW/Include/GL/glew.h>
#include <GLM/include/fwd.hpp>

#include "Shader.h"
#include "UTILS/include/Model.h"
#include "UTILS/include/FractalNoise.h"
#include "UTILS/include/Constants.h"
class Terrain
{


public:
	struct TerrainVertex
	{
		glm::vec3 Position;
		glm::vec2 UVCoord;
	};
	Terrain();
	void DrawTerrain(glm::mat4& terrainModel, glm::mat4& cameraView, Shader& terrainShader, int subroutineIndex);
	std::vector<TerrainVertex> GetTerrainVertices();
private:
	void SetupTerrain();
	unsigned int VAO, VBO, EBO;
	std::vector<TerrainVertex> vertices;
	std::vector<unsigned int> indices;
};


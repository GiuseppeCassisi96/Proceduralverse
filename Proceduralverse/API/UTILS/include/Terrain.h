#pragma once
#define GLEW_STATIC
#include <vector>
#include <GLM/include/fwd.hpp>
#include "Shader.h"
#include "Texture.h"
#include "UTILS/include/Constants.h"
#include "UTILS/include/Movement.h"
#include "UTILS/include/Mesh.h"
class Terrain
{


public:
	struct TerrainVertex
	{
		glm::vec3 Position;
		glm::vec2 UVCoord;
	};
	Terrain(const std::vector<float>& heightMap);
	void DrawTerrain(glm::mat4& terrainModel, glm::mat4& cameraView, Shader& terrainShader,
	                 Texture& grassTexture, Texture& snowTexture);
	std::vector<TerrainVertex> GetTerrainVertices();

	
private:
	void SetupTerrain(const std::vector<float>& heightMap);
	unsigned int VAO, VBO, EBO;
	std::vector<unsigned int> indices;
	std::vector<TerrainVertex> vertices;
};


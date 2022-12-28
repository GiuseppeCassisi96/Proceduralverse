#pragma once
#include <vector>
#include <GLM/include/fwd.hpp>

#include "Model.h"
#include "Shader.h"
#include "Terrain.h"

class Tree
{
	
public:
	Tree(int iterations,std::vector < glm::mat4>& treePos, const std::vector<float>& heightMap,
		 Terrain& terrain);
	void FillTreeArray(std::vector<glm::mat4>& treePos, const std::vector<float>& biomeMap);
	void DrawTrees(glm::mat4& treeModel, glm::mat4 cameraView ,glm::mat3& treeNormal, 
		Shader& treeShader, Model& tree, int subroutineIndex);
private:
	Terrain terrain;
	int iterations;
	glm::vec3 GenerateRandPoint(int& indexXpos, int& indexZpos, float& biomeValue, const std::vector<float>& biomeMap);
	
};

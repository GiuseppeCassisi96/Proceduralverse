#pragma once
#include <queue>
#include <vector>
#include <GLM/include/fwd.hpp>
#include <GLM/include/vec2.hpp>
#include <GLM/include/vec3.hpp>

#include "Shader.h"
#include "Terrain.h"
#include "UTILS/include/Constants.h"

class Tree
{
	
public:
	Tree(int treeCount,  const std::vector<float>& heightMap);
	void FillTreeArray();
	std::vector<glm::vec3> treePositions;
	void DrawTrees(glm::mat4& treeModel, glm::mat4 cameraView ,glm::mat3& treeNormal, 
		Shader& treeShader, Model& tree, int subroutineIndex);
private:
	int treeCount;
	std::vector<float> heigthMap;
	glm::vec3 GenerateRandPointAroundAPoint(int& indexXpos, int& indexZpos);
	
};

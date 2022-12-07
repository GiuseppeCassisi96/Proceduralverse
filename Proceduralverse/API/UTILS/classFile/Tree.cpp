#include "UTILS/include/Tree.h"

#include <GLM/include/gtc/matrix_inverse.inl>


Tree::Tree(int treeCount, const std::vector<float>& heightMap) : treeCount(treeCount), heigthMap(heightMap)
{
	FillTreeArray();
}


void Tree::FillTreeArray()
{
	glm::vec3 newPoint;
	int index = 0;
	while(index < treeCount)
	{
		int indexXPos = 0;
		int indexZPos = 0;
		newPoint = GenerateRandPointAroundAPoint(indexXPos, indexZPos);
		if(heigthMap[indexXPos + indexZPos * MESH_RESOLUTION] >= -0.8f && 
			heigthMap[indexXPos + indexZPos * MESH_RESOLUTION] <= -0.4f)
		{
			treePositions.emplace_back(newPoint);
			index++;
		}
	}

  
}

void Tree::DrawTrees(glm::mat4& treeModel, glm::mat4 cameraView, glm::mat3& treeNormal, Shader& treeShader
	, Model& tree, int subroutineIndex)
{
	for (int i = 0; i < treePositions.size(); i++)
	{
		treeModel = glm::mat4{ 1.0f };
		treeNormal = glm::mat3{ 1.0f };
		treeModel = glm::translate(treeModel, treePositions[i]);
		treeModel = glm::rotate(treeModel, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		treeModel = glm::scale(treeModel, glm::vec3(0.1f));
		/*We need also the matrix for normals transformation, which is the inverse of the
		  transpose of the 3x3 submatrix(upper left) of the modelview. We do not consider
		  the 4th column because we do not need translations for normals.*/
		treeNormal = inverseTranspose(glm::mat3(cameraView * treeModel));
		treeShader.UseProgram();
		treeShader.SetSubroutine("TreeVertShader", GL_VERTEX_SHADER);
		treeShader.SetSubroutine("TreeFrag", GL_FRAGMENT_SHADER);
		treeShader.SetUniformMatrix4("model", treeModel);
		treeShader.SetUniformMatrix4("view", cameraView);
		treeShader.SetUniformMatrix3("normalMatrix", treeNormal);
		tree.DrawModel();
	}
}

glm::vec3 Tree::GenerateRandPointAroundAPoint(int& indexXpos, int& indexZpos)
{
	indexXpos = rand() % MESH_RESOLUTION;
	indexZpos = rand() % MESH_RESOLUTION;
	const float newX = static_cast<float>(indexXpos) * XDIM - 1.0f;
	const float newZ = static_cast<float>(indexZpos) * YDIM - 1.0f;
	const glm::vec3 newRandomPoint = glm::vec3(newX, 0.0f, newZ);
	return  newRandomPoint;
}


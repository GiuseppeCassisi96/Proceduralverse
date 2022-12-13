#include "UTILS/include/Tree.h"
#include <GLM/include/gtc/matrix_inverse.inl>

Tree::Tree(int treeCount, const std::vector<float>& heightMap, Terrain& terrain) : treeCount{treeCount}, heigthMap{heightMap}, terrain{terrain}
{
	treePositions.reserve(treeCount);
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
		float heightValue = 0.0f;
		float height;
		newPoint = GenerateRandPoint(indexXPos, indexZPos, height);
		if(height >= -0.8f &&
			height <= -0.4f)
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
		treeModel = glm::scale(treeModel, glm::vec3(0.05f));
		/*We need also the matrix for normals transformation, which is the inverse of the
		  transpose of the 3x3 submatrix(upper left) of the modelview. We do not consider
		  the 4th column because we do not need translations for normals.*/
		treeNormal = inverseTranspose(glm::mat3(cameraView * treeModel));

		treeShader.SetSubroutine("TreeVertShader", GL_VERTEX_SHADER);
		treeShader.SetSubroutine("TreeFrag", GL_FRAGMENT_SHADER);
		treeShader.SetUniformMatrix4("model", treeModel);
		treeShader.SetUniformMatrix4("view", cameraView);
		treeShader.SetUniformMatrix3("normalMatrix", treeNormal);
		tree.DrawModel();
	}
}

glm::vec3 Tree::GenerateRandPoint(int& indexXpos, int& indexZpos, float& heightValue)
{
	indexXpos = rand() % MESH_RESOLUTION;
	indexZpos = rand() % MESH_RESOLUTION;
	Terrain::TerrainVertex vertexInfo = terrain.GetTerrainVertices()[indexXpos + indexZpos * MESH_RESOLUTION];
	heightValue = heigthMap[indexXpos + indexZpos * MESH_RESOLUTION];
	const float newX = vertexInfo.Position.x * XDIM;
	const float newY = heightValue * HEIGHT_SCALE;
	const float newZ = vertexInfo.Position.z * ZDIM;
	return {newX, newY, newZ};
}


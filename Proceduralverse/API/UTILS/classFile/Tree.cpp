#include "UTILS/include/Tree.h"



Tree::Tree(int iterations, std::vector < glm::mat4>& treePos, const std::vector<float>& heightMap, Terrain& terrain)
: iterations{iterations}, terrain{terrain}
{
	FillTreeArray(treePos, heightMap);
}


void Tree::FillTreeArray(std::vector<glm::mat4>& treePos, const std::vector<float>& biomeMap)
{
	int index = 0;
	while(index < iterations)
	{
		int indexXPos = 0;
		int indexZPos = 0;
		float biomeValue;
		const glm::vec3 newPoint = GenerateRandPoint(indexXPos, indexZPos, biomeValue, biomeMap);
		if(biomeValue > -0.4f)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, newPoint);
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.05f));
			treePos[index] = model;
			index++;
		}
		
	}

  
}

void Tree::DrawTrees(glm::mat4& treeModel, glm::mat4 cameraView, glm::mat3& treeNormal, Shader& treeShader
	, Model& tree, int subroutineIndex)
{
	treeShader.SetSubroutine("TreeVertShader", GL_VERTEX_SHADER);
	treeShader.SetSubroutine("TreeFrag", GL_FRAGMENT_SHADER);
	treeShader.SetUniformMatrix4("view", cameraView);
	tree.DrawModel();
	
}

glm::vec3 Tree::GenerateRandPoint(int& indexXpos, int& indexZpos, float& biomeValue, const std::vector<float>& biomeMap)
{
	indexXpos = rand() % MESH_RESOLUTION;
	indexZpos = rand() % MESH_RESOLUTION;
	Terrain::TerrainVertex vertexInfo = terrain.GetTerrainVertices()[indexXpos + indexZpos * MESH_RESOLUTION];
	biomeValue = biomeMap[indexXpos + indexZpos * MESH_RESOLUTION];
	const float newX = vertexInfo.Position.x * XDIM;
	const float newY = vertexInfo.Position.y * HEIGHT_SCALE;
	const float newZ = vertexInfo.Position.z * ZDIM;
	return {newX, newY, newZ};
}


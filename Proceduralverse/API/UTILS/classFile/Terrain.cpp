#include "UTILS/include/Terrain.h"

Terrain::Terrain()
{
    vertices.reserve(MESH_RESOLUTION * MESH_RESOLUTION);
    indices.reserve((MESH_RESOLUTION - 1) * (MESH_RESOLUTION - 1) * 6);
    SetupTerrain();
}

void Terrain::SetupTerrain()
{

    for (int i = 0; i < MESH_RESOLUTION; i++)
    {
        for (int j = 0; j < MESH_RESOLUTION; j++)
        {
            const auto fXDim = static_cast<float>(XDIM);
            const auto fYDim = static_cast<float>(YDIM);
            const auto fi = static_cast<float>(i);
            const auto fj = static_cast<float>(j);
            const auto fMeshResolution = static_cast<float>(MESH_RESOLUTION);
            TerrainVertex tempVertex;
            tempVertex.Position = glm::vec3
            (
                i
                , 0.0f //Y
                ,j
            );
            tempVertex.UVCoord = glm::vec2
            (
                fi / fMeshResolution, //U
                fj / fMeshResolution  //V
            );
            vertices.push_back(tempVertex);
        }
    }


    int rowOffset = 0;
    for(int i = 0; i < MESH_RESOLUTION -1; i++)
    {
	    for(int j = 0; j < MESH_RESOLUTION -1; j++)
	    {
            //First triangle
            indices.emplace_back(j + rowOffset + MESH_RESOLUTION);
            indices.emplace_back(j + rowOffset);
            indices.emplace_back(j + 1 + rowOffset);
            

            //Second triangle
            indices.emplace_back(j + 1 + rowOffset);
            indices.emplace_back(j + rowOffset + MESH_RESOLUTION + 1);
            indices.emplace_back(j + rowOffset + MESH_RESOLUTION);
            
	    }
        rowOffset += MESH_RESOLUTION;
    }


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
   

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TerrainVertex), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}



void Terrain::DrawTerrain(glm::mat4& terrainModel, glm::mat4& cameraView, Shader& terrainShader)
{
    terrainModel = glm::mat4{ 1.0f };
    terrainModel = glm::translate(terrainModel, glm::vec3(0.0f));
    terrainModel = glm::rotate(terrainModel, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    terrainModel = glm::scale(terrainModel, glm::vec3(XDIM, 1.0f, YDIM));
    terrainShader.UseProgram();
    terrainShader.SetUniformMatrix4("model", terrainModel);
    terrainShader.SetUniformMatrix4("view", cameraView);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,  static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::vector<Terrain::TerrainVertex> Terrain::GetTerrainVertices()
{
    return vertices;
}


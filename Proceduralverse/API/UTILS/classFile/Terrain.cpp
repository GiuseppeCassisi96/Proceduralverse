#include "UTILS/include/Terrain.h"




Terrain::Terrain(const std::vector<float>& heightMap) :VAO{0}, VBO{0}, EBO{0}
{
    constexpr int verticesSize = MESH_RESOLUTION * MESH_RESOLUTION;
    constexpr int indicesSize = (MESH_RESOLUTION - 1) * (MESH_RESOLUTION - 1) * 6;
    vertices.reserve(verticesSize);
    indices.reserve(indicesSize);
    SetupTerrain(heightMap);
}

void Terrain::SetupTerrain(const std::vector<float>& heightMap)
{
    for (int i = 0; i < MESH_RESOLUTION; i++)
    {
        for (int j = 0; j < MESH_RESOLUTION; j++)
        {
            const auto fi = static_cast<float>(i);
            const auto fj = static_cast<float>(j);
            constexpr auto fMeshResolution = static_cast<float>(MESH_RESOLUTION);
            TerrainVertex tempVertex {};
            tempVertex.Position = glm::vec3
            (
                i
                , heightMap[i + j * MESH_RESOLUTION] //Y
                ,j
            );
            tempVertex.UVCoord = glm::vec2
            (
                NUMBER_OF_TILE * fi / fMeshResolution, //U
                NUMBER_OF_TILE * fj / fMeshResolution  //V
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



void Terrain::DrawTerrain(glm::mat4& terrainModel, glm::mat4& cameraView, Shader& terrainShader,
                          Texture& grassTexture, Texture& snowTexture)
{
    terrainModel = glm::mat4{ 1.0f };
    terrainModel = glm::translate(terrainModel, glm::vec3(0.0f));
    terrainModel = glm::rotate(terrainModel, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    terrainModel = glm::scale(terrainModel, glm::vec3(XDIM, 1.0f, ZDIM));

    terrainShader.UseProgram();
    terrainShader.SetSubroutine("TerrainGeneration", GL_VERTEX_SHADER);
    terrainShader.SetSubroutine("TerrainFrag", GL_FRAGMENT_SHADER);
    terrainShader.SetUniformMatrix4("model", terrainModel);
    terrainShader.SetUniformMatrix4("view", cameraView);
    terrainShader.SetUniformInt("grass", 1);
    terrainShader.SetUniformInt("snow", 2);
    grassTexture.BindTexture(GL_TEXTURE1);
    snowTexture.BindTexture(GL_TEXTURE2);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,  static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::vector<Terrain::TerrainVertex> Terrain::GetTerrainVertices()
{
    return  vertices;
}







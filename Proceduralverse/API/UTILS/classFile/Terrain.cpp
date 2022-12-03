#include "UTILS/include/Terrain.h"

Terrain::Terrain(int meshRes) : meshResolution(meshRes)
{
    SetupTerrain();
}

void Terrain::SetupTerrain()
{
    std::cout << "XDim: " << "\n";
    std::cin >> XDim;
    std::cout << "YDim: " << "\n";
    std::cin >> YDim;

    for (int i = 0; i < meshResolution; i++)
    {
        for (int j = 0; j < meshResolution; j++)
        {
            const auto fXDim = static_cast<float>(XDim);
            const auto fYDim = static_cast<float>(YDim);
            const auto fi = static_cast<float>(i);
            const auto fj = static_cast<float>(j);
            const auto fMeshResolution = static_cast<float>(meshResolution);
            TerrainVertex tempVertex;
            tempVertex.Position = glm::vec3
            (
                -fXDim / 2.0f + fXDim * fi / fMeshResolution //X
                , 0.0f //Y
                , -fYDim / 2.0f + fYDim * fj / fMeshResolution //Z
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
    for(int i = 0; i < meshResolution-1; i++)
    {
	    for(int j = 0; j < meshResolution-1; j++)
	    {
            //First triangle
            indices.emplace_back(j + rowOffset + meshResolution);
            indices.emplace_back(j + rowOffset);
            indices.emplace_back(j + 1 + rowOffset);
            

            //Second triangle
            indices.emplace_back(j + 1 + rowOffset);
            indices.emplace_back(j + rowOffset + meshResolution + 1);
            indices.emplace_back(j + rowOffset + meshResolution);
            
	    }
        rowOffset += meshResolution;
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

void Terrain::DrawTerrain()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,  static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#include <iostream>
#define GLEW_STATIC
#include "GLEW/Include/GL/glew.h"
#include "GLFW/Include/glfw3.h"
#include "UTILS/include/Movement.h"
#include "UTILS/include/Shader.h"
#include "UTILS/include/Terrain.h"
#include "UTILS/include/Texture.h"
#include "UTILS/include/Tree.h"


glm::mat4 cameraView{ 1.0f };
glm::mat4 proj = glm::perspective(45.0f, WIDTH / HEIGHT, 0.1f, 1000000.0f);
Movement cameraMove{ glm::vec3(0.0f,0.0f,7.0f),cameraView };
//Terrain generator parameters
float heightScale = 20.0f;
float frequency = 3.0f;
int octaves = 10;
float amplitude = 0.5f;
float seed = 1.0f;
FractalNoise ElevationMap{ MESH_RESOLUTION,octaves,frequency,amplitude, seed };
FractalNoise BiomeMap{ MESH_RESOLUTION,octaves,frequency,amplitude, seed};



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cameraMove.Rotate(xpos, ypos);
}

bool isWireFrame = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action ,int mode)
{
    if(key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        isWireFrame = !isWireFrame;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        ElevationMap.CreateHeightMap();
        BiomeMap.CreateHeightMap();
    }

}

int main(void)
{
    GLFWwindow* window;
    
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(1920, 1080, "Proceduralverse", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error to initialize GLEW" << "\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    Shader treeShader("src/Assets/Shaders/TreeShader.vert",
        "src/Assets/Shaders/TreeShader.frag");

    Shader terrainShader{
    "src/Assets/Shaders/Proceduralverse.vert",
    "src/Assets/Shaders/Proceduralverse.frag" };

    
    //I'm setting the terrain generator parameters which are editable at runtime 
    terrainShader.UseProgram();
    terrainShader.SetUniformFloat("frequency", frequency);
    terrainShader.SetUniformInt("octaves", octaves);
    terrainShader.SetUniformFloat("amplitude", amplitude);
    terrainShader.SetUniformFloat("seed", seed);
    terrainShader.SetUniformFloat("heightScale", heightScale);
    terrainShader.SetUniformMatrix4("proj", proj);

    ElevationMap.CreateHeightMap();
    BiomeMap.CreateHeightMap();

    Terrain terrain{};
    Model tree{ "src/Assets/Models/tree_obj.obj" };
    Tree treePositionManager{600,BiomeMap.HeightMap};

    glm::mat4 terrainModel{ 1.0f };
    glm::mat4 treeModel{ 1.0f };
	glm::mat3 treeNormal{ 1.0f };

    treeShader.UseProgram();
    treeShader.SetUniformMatrix4("proj", proj);

    Texture texture{ ElevationMap.HeightMap, GL_TEXTURE0,MESH_RESOLUTION,terrainShader };
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.35f, 0.40f, 1.0f, 1.0f);
        cameraMove.Move(window, cameraView);
        if (isWireFrame)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        treePositionManager.DrawTrees(treeModel, cameraView, treeNormal, treeShader, tree);

        terrain.DrawTerrain(terrainModel,cameraView,terrainShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    terrainShader.DeleteProgram();
    treeShader.DeleteProgram();
    glfwTerminate();
    return 0;
}
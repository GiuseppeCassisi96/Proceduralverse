#include <iostream>
#define GLEW_STATIC
#include "GLEW/Include/GL/glew.h"
#include "GLFW/Include/glfw3.h"
#include "UTILS/include/Movement.h"
#include "UTILS/include/Shader.h"
#include "UTILS/include/Terrain.h"
#include "UTILS/include/Model.h"
#include "UTILS/include/FractalNoise.h"


struct vertex
{
    glm::vec3 Position;
    glm::vec2 UVCoord;
};

int meshRes = 400;
glm::mat4 cameraView{ 1.0f };
glm::mat4 proj = glm::perspective(45.0f, WIDTH / HEIGHT, 0.1f, 1000000.0f);
Movement cameraMove{ glm::vec3(0.0f,0.0f,4.0f),cameraView };
//Terrain generator parameters
float heightScale = 120;
float frequency = 0.9f;
int octaves = 10;
float amplitude = 1.0f;
int segmentsPerEdge = 30;
float seed = 1.5f;
FractalNoise TreeBiomeMap{ meshRes, meshRes,octaves,frequency,amplitude, seed};



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
        TreeBiomeMap.CreateHeightMap();
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
    terrainShader.SetUniformInt("segmentsPerEdge", segmentsPerEdge);

    Terrain terrain{meshRes};
    Model Tree{ "src/Assets/Models/tree_obj.obj" };
   
    TreeBiomeMap.CreateHeightMap();

    glm::mat4 terrainModel{ 1.0f };
    glm::mat4 treeModel{ 1.0f };
	glm::mat3 treeNormal{ 1.0f };

    terrainShader.SetUniformMatrix4("proj", proj);
    treeShader.UseProgram();
    treeShader.SetUniformMatrix4("proj", proj);

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


        treeModel = glm::mat4{ 1.0f };
        treeNormal = glm::mat3{ 1.0f };
        treeModel = glm::translate(treeModel, glm::vec3(0.0f));
        treeModel = glm::rotate(treeModel, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        treeModel = glm::scale(treeModel, glm::vec3(0.5f));
        /*We need also the matrix for normals transformation, which is the inverse of the
     *transpose of the 3x3 submatrix(upper left) of the modelview. We do not consider
     *the 4th column because we do not need translations for normals.*/
        treeNormal = inverseTranspose(glm::mat3(cameraView * treeModel));
        treeShader.UseProgram();
        treeShader.SetUniformMatrix4("model", treeModel);
        treeShader.SetUniformMatrix4("view", cameraView);
        treeShader.SetUniformMatrix3("normalMatrix", treeNormal);
        Tree.DrawModel();

        terrainModel = glm::mat4{ 1.0f };
        terrainModel = glm::translate(terrainModel, glm::vec3(0.0f));
        terrainModel = glm::rotate(terrainModel, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        terrainModel = glm::scale(terrainModel, glm::vec3(1.0f, 1.0f, 1.0f));
        terrainShader.UseProgram();
        terrainShader.SetUniformMatrix4("model", terrainModel);
        terrainShader.SetUniformMatrix4("view", cameraView);
        terrain.DrawTerrain();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    terrainShader.DeleteProgram();
    treeShader.DeleteProgram();
    glfwTerminate();
    return 0;
}
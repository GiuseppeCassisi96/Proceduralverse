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
float frequency = 2.0f;
int octaves = 10;
float amplitude = 0.9f;
float seed = 1.0f;
std::vector<float> ElevationMap;
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


}

int main(void)
{
    ElevationMap.reserve(MESH_RESOLUTION * MESH_RESOLUTION);
    GLFWwindow* window;
    
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    Shader ProceduralVerseShader{
    "src/Assets/Shaders/Proceduralverse.vert",
    "src/Assets/Shaders/Proceduralverse.frag" };
    Shader compute {"src/Assets/Shaders/Proceduralverse.comp"};

    compute.UseProgram();
    compute.SetUniformFloat("amplitude", amplitude);
    compute.SetUniformFloat("frequency", frequency);
    compute.SetUniformInt("octaves", octaves);
    compute.SetUniformFloat("seed", seed);

    Texture texture{ GL_TEXTURE0 };
    texture.UseTexture(compute);
    compute.DispatchCompute();
    ElevationMap = texture.GetValuesOfMap();
  
    //I'm setting the terrain generator parameters which are editable at runtime 
    ProceduralVerseShader.UseProgram();
    ProceduralVerseShader.SetUniformMatrix4("proj", proj);
    ProceduralVerseShader.SetUniformFloat("heightScale", HEIGHT_SCALE);

    Terrain terrain{ ElevationMap };
    Model tree{ "src/Assets/Models/tree_obj.obj" };
    Tree treePositionManager{200,ElevationMap, terrain};

    glm::mat4 terrainModel{ 1.0f };
    glm::mat4 treeModel{ 1.0f };
	glm::mat3 treeNormal{ 1.0f };

    
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

       

        terrain.DrawTerrain(terrainModel, cameraView, ProceduralVerseShader, 0, ElevationMap, texture);
        treePositionManager.DrawTrees(treeModel, cameraView, treeNormal, ProceduralVerseShader, tree, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ProceduralVerseShader.DeleteProgram();
    glfwTerminate();
    return 0;
}
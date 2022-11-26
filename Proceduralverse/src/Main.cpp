#include <iostream>
#define GLEW_STATIC
#include <vector>

#include "GLEW/Include/GL/glew.h"
#include "GLFW/Include/glfw3.h"
#include "UTILS/include/ErrorCheck.h"
#include "UTILS/include/Transform.h"
#include "UTILS/include/Movement.h"
#include "UTILS/include/Shader.h"
#include "UTILS/include/Texture.h"

struct vertex
{
    glm::vec3 Position;
    glm::vec2 UVCoord;
};


Transform cameraTr{};
Movement cameraMove{ glm::vec3(0.0f,20.0f,16.0f),cameraTr.view };
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cameraMove.Rotate(xpos, ypos);
}

bool isWireFrame = false;

void ChangeRenderMode(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_P))
    {
        isWireFrame = !isWireFrame;
    }

	if(isWireFrame)
	{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

    Shader shader{
	"src/Assets/Shaders/Proceduralverse.vert",
	"src/Assets/Shaders/Proceduralverse.tesc",
	"src/Assets/Shaders/Proceduralverse.tese",
	"src/Assets/Shaders/Proceduralverse.frag" };
    Transform tr{};
    shader.UseProgram();
    shader.SetUniformFloat("frequency", 0.5f);
    shader.SetUniformFloat("octaves", 10.0f);
    shader.SetUniformFloat("amplitude", 60.0f);

    /*Texture texture{ "C:/UNIMI/iceland_heightmap.png" };
    int XResolution = texture.width, YResolution = texture.height;*/
    int XResolution = 600, YResolution = 600;
    std::vector<vertex> vertices;
    int numberOfPatch = 20;
    for(int i = 0; i < numberOfPatch; i++)
    {
	    for(int j = 0; j < numberOfPatch; j++)
	    {
            const auto fXResolution = static_cast<float>(XResolution);
            const auto fYResolution = static_cast<float>(YResolution);
            const auto fi = static_cast<float>(i);
            const auto fj = static_cast<float>(j);
            const auto fNumberOfPatch = static_cast<float>(numberOfPatch);
            vertex tempVertex;
            //First vertex of patch
            tempVertex.Position = glm::vec3
	    	(
                -fXResolution / 2.0f + fXResolution * fi / fNumberOfPatch //X
                , 0.0f //Y
                ,-fYResolution / 2.0f + fYResolution * fj / fNumberOfPatch //Z
            );
            tempVertex.UVCoord = glm::vec2
	    	(
                fi / fNumberOfPatch, //U
                fj / fNumberOfPatch  //V
            );
            vertices.push_back(tempVertex);

            //Second vertex of patch
            tempVertex.Position = glm::vec3
	    	(
                -fXResolution / 2.0f + fXResolution * (fi + 1) / fNumberOfPatch //X
                , 0.0f //Y
                , -fYResolution / 2.0f + fYResolution * fj / fNumberOfPatch //Z
            );

            tempVertex.UVCoord = glm::vec2
	    	(
                (fi + 1) / fNumberOfPatch, //U
                fj / fNumberOfPatch //V
            );
            vertices.push_back(tempVertex);

            //Third vertex of patch
            tempVertex.Position = glm::vec3
	    	(
                -fXResolution / 2.0f + fXResolution * fi / fNumberOfPatch //X
                ,0.0f //Y
                , -fYResolution / 2.0f + fYResolution * (fj + 1) / fNumberOfPatch //Z
            );
            tempVertex.UVCoord = glm::vec2
	    	(
                fi / fNumberOfPatch, //U
	    		(fj + 1) / fNumberOfPatch //V
            );
            vertices.push_back(tempVertex);

            //Fourth vertex of patch
            tempVertex.Position = glm::vec3
	    	(
                -fXResolution / 2.0f + fXResolution * (fi + 1) / fNumberOfPatch //X
                , 0.0f //Y
                , -fYResolution / 2.0f + fYResolution * (fj + 1) / fNumberOfPatch //Z
            );
            tempVertex.UVCoord = glm::vec2
	    	(
                (fi + 1) / fNumberOfPatch, //U 
                (fj + 1) / fNumberOfPatch //V
            );
            vertices.push_back(tempVertex);
	    }
    }

    GLuint verticesVBO, verticesVAO;
    glGenVertexArrays(1, &verticesVAO);
    glGenBuffers(1, &verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBindVertexArray(verticesVAO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_DYNAMIC_DRAW);

    GLDebugError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0));
    glEnableVertexAttribArray(0);

    GLDebugError(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float))));
    glEnableVertexAttribArray(1);

    //Specifies the number of vertices per patch
    glPatchParameteri(GL_PATCH_VERTICES, 4);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.15f, 0.35f, 1.0f, 1.0f);

        cameraMove.Move(window, cameraTr.view);
        shader.UseProgram();
        shader.SetUniformMatrix4("proj", tr.proj);
        shader.SetUniformMatrix4("model", tr.model);
        shader.SetUniformMatrix4("view", cameraTr.view);
        ChangeRenderMode(window);
        glBindVertexArray(verticesVAO);
        glDrawArrays(GL_PATCHES, 0, 4 * numberOfPatch * numberOfPatch);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
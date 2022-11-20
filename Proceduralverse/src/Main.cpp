#include <iostream>
#define GLEW_STATIC
#include "GLEW/Include/GL/glew.h"
#include "GLFW/Include/glfw3.h"



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



    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.15f, 0.35f, 1.0f, 1.0f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
void processInput(GLFWwindow* window , float* gradientScale)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Adjust the color gradient scale with the DOWN arrow key
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        *gradientScale -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        *gradientScale += 0.01f;
    // Ensure the gradient scale doesn't go below 0
    *gradientScale = std::max(*gradientScale, 0.0f);
}

int main(void)
{
    int y = 5;
    int* z = &y;
    const int* const* const x = &z;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW NOT OK" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    glfwSwapInterval(1);

    VertexArray va;
    unsigned int indiceis[6] = {
        3,4,5,
        0,1,2
    };
    const float depth = 0.45;
    float pos[] = {
       -1.0f, 1.0f,-0.5f,
        1.0f, 0.0f,0.0f,

        1.0f, 1.0f, -0.5f,
        1.0f, 0.0f,0.0f,

        0.0f,-1.0f, -1.0f,
        1.0f, 0.0f,0.0f,



       -1.0f,-1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f,-1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, -1.0f,
        0.0f, 0.0f, 1.0f
    };
    GLCall(glEnable(GL_DEPTH_TEST));
    VertexBuffer vb((void*)pos, sizeof(pos));
    IndexBuffer ib(indiceis, 6);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);
    va.Bind();
    ib.Bind();

    //shader program
    Shader shader = Shader("res/shaders/basics.shader");
    shader.Bind();
    /* Loop until the user closes the window */
    float color = 0.5f;
    float increment = 0.05f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        processInput(window, &color);
        /* Render here */
        //shader.SetUniform4f("color", color, 0.3f, 0.8f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        glEnd();
        color += increment;
        ;       if (color > 1) increment = -0.05f;
        else if (color < 0) increment = 0.05f;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
/*
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum  class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("shader") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, 0);
    glCompileShader(id);

    //error checking
    int isGood;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isGood);
    if (isGood == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* log = (char*)alloca(length);
        glGetShaderInfoLog(id, 1024, 0, log);
        std::cout << "Error in Compilation" << "\n" << log << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Shader Compiled Succesfuly!" << std::endl;
    }

    return id;
}
static unsigned int CreateShader(const char* vertextShader, const char* fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int isLinked;

    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* log = (char*)alloca(length);
        glGetProgramInfoLog(program, 1024, 0, log);
        std::cout << "There was an error while linking. \n" << log << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Program Linked Succesfuly!" << std::endl;
    }
    return program;
}*/
void processInput(GLFWwindow* window, float* gradientScale)
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


   // ShaderProgramSource source = ParseShader("res/shaders/basics.shader");
    VertexArray va;

    unsigned int indiceis[6] = {
        0,1,2,
        3,1,2
    };
    float pos[] = {
       -0.5f,-0.5f,
       -0.5f, 0.5f,
        0.5f,-0.5f,
        0.5f, 0.5f
    };
    VertexBuffer vb((void*)pos, sizeof(pos));
    vb.Bind();

    IndexBuffer ib(indiceis, 6);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    va.Bind();
    ib.Bind();
    va.UnBind();
    va.Bind();

    //shader program
    //unsigned int program = CreateShader(source.VertexSource.c_str(), source.FragmentSource.c_str());
    Shader shader("res/shaders/basics.shader");
    shader.Bind();
    /* Loop until the user closes the window */
    float color = 0.1;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &color);
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);
        shader.SetUniform1f("color", color);
        //glUniform1f(glGetUniformLocation(program, "color"), color);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
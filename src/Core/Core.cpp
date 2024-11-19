#include "Core.h"
#include "Renderer/Shader.h"
#include "Tools/ErrorChecker.h"
#include "Tools/Enums.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <glad/glad.h>
#include <string>

namespace Core 
{
    GLFWwindow* window;
    GLFWmonitor* monitor;
    int frameCount;
    float deltaTime;
    double previousTime;
    clock_t start, end;


    void initalize()
    {
        CheckError((bool)glfwInit(), Error::INITIALIZATION_GLFW);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback(errorCallback);

        monitor = glfwGetPrimaryMonitor();
        window = glfwCreateWindow(100, 100, "window", NULL, NULL);

        CheckError((bool)window, Error::CREATE_WINDOW);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        CheckError((bool)gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), Error::LOAD_GLAD);
    }

    void beginFrame()
    {
        start = clock();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void endFrame()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void cleanUp()
    {
        glfwTerminate();
    }
    
    GLFWwindow* getWindow()
    {
        return window;
    }
    
    bool windowIsOpen()
    {
        return glfwWindowShouldClose(window);
    }

    float getDeltaTime()
    {
        return deltaTime;
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void errorCallback(int error_code, const char *description)
    {
        std::cout << description << "error code: " << error_code << std::endl;
    }

    void setWindowTitle(std::string title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }
    
    void setWindowSize(int width, int heigth)
    {
        glfwSetWindowSize(window, width, heigth);
    }

    int getWindowedWidth()
    {
        int width;
        glfwGetWindowSize(window, &width, nullptr);
        return width;
    }

    int getWindowedHeight()
    {
        int height;
        glfwGetWindowSize(window, nullptr, &height);
        return height;
    }
}
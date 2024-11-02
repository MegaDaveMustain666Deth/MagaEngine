#include <Core.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <Shader.h>
#include <time.h>
#include <glad/glad.h>
#include <string>
#include <ErrorChecker.h>
#include <Enums.h>

namespace Core 
{
    GLFWwindow* window;
    GLFWmonitor* monitor;
    int frameCount;
    float deltaTime;
    double previousTime;
    Shader shader;
    clock_t start, end;


    void initalize()
    {

        CheckError((bool)glfwInit(), Error::INITIALIZATION_GLFW);

        glfwSetErrorCallback(errorCallback);

        monitor = glfwGetPrimaryMonitor();
        window = glfwCreateWindow(100, 100, "window", NULL, NULL);

        CheckError((bool)window, Error::CREATE_WINDOW);

        glfwMakeContextCurrent(window);

        CheckError((bool)gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), Error::LOAD_GLAD);

        shader.load("res/vertex.vert", "res/fragment.frag");

        glEnable(GL_MULTISAMPLE);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }

    void beginFrame()
    {
        start = clock();
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void endFrame()
    {
        glfwSwapBuffers(window);
        end = clock();

        double currentTime = glfwGetTime();

        frameCount++;
        if ( currentTime - previousTime >= 1.0 )
        {
            std::string fps = (std::string)"windwow" + " fps: " + std::to_string(frameCount);
            setWindowTitle(fps);

            frameCount = 0;
            previousTime = currentTime;
        }
        deltaTime = ((float) end - start) / CLOCKS_PER_SEC;
    }

    void cleanUp()
    {
        shader.cleanUp();

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
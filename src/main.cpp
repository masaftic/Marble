#include<iostream>
#include<sstream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "game.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCREEN_WIDTH  = 1000;
const unsigned int SCREEN_HEIGHT = 800;

Game Marble(SCREEN_WIDTH, SCREEN_HEIGHT);


int main()
{
    // Initialize GLFW
    glfwInit();
    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a GLFWwindow object of width by height pixels, naming it "Marble"
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Marble", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }


    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    Marble.Init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int frameCount = 0;
    float lastTime = glfwGetTime();
    
    glfwSwapInterval(1);

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        frameCount++;
        float deltaFps = currentFrame - lastTime;
        if (deltaFps >= 1.0f) {
            float fps = frameCount / deltaFps;

            std::stringstream ss;
            ss << " [" << fps << " FPS]";

            glfwSetWindowTitle(window, ss.str().c_str());

            frameCount = 0;
            lastTime = currentFrame;
        }

        // make sure delta time doesn't get too big
        if (deltaTime > 0.15f)
            deltaTime = 0.15f;



        glfwPollEvents();

        Marble.ProcessInput(window, deltaTime); 

        Marble.Update(deltaTime);

        glClearColor(0.3f, 0.6f, 0.84f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Marble.Render();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.

    Marble.UpdateResolution(width, height);
    glViewport(0, 0, width, height);
}


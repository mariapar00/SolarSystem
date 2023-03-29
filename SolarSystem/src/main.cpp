#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/model.h"
#include "graphics/models/sun.hpp"

#include "modules/screen.h"
#include "modules/camera.h"
#include "modules/keyboard.h"

void processInput();

// screen
Screen screen;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 50.0f));

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// paused
bool sleep = 0;
float pauseFrame;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
   

    if (!screen.init()) {
        std::cout << "Could not create window." << std::endl;
        glfwTerminate();
        return -1;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    screen.setParameters();

    glEnable(GL_DEPTH_TEST);

    // shaders
    // -------
    Shader shader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    Shader sunShader("shaders/vertexShader.vs", "shaders/sun.fs");

    Model earth(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.2f));
    earth.loadModel("C:/Users/Maria/Documents/grafika/SolarSystem/resources/objects/Earth/Globe.obj");

    Model moon(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.3f));
    moon.loadModel("C:/Users/Maria/Documents/grafika/SolarSystem/resources/objects/Moon/planet.obj");

    Sun sun(glm::vec3(1.0f), glm::vec3(3.0f), glm::vec3(20.0f), glm::vec3(1.0f),
        1.0f, 0.07f, 0.032f,
        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.5f));

    sun.loadModel("C:/Users/Maria/Documents/grafika/SolarSystem/resources/objects/Sun/planet.obj");

    // render loop
    // -----------
    while (!screen.shouldClose())
    { 
        // input
        processInput();
   
        if (!sleep) {   // when paused do not update/render but process input and poll events
            // per-frame time logic
            // --------------------
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // render
            screen.update();

            shader.activate();
            shader.setVec3("viewPos", camera.Position);

            sun.pointLight.render(shader);


            // create transformation for screen
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            view = camera.GetViewMatrix();
            projection = glm::perspective(glm::radians(camera.Zoom), (float)screen.SCR_WIDTH / (float)screen.SCR_HEIGHT, 0.1f, 100.0f);

            shader.setMat4("view", view);
            shader.setMat4("projection", projection);

            earth.Draw(shader, "earth");
            moon.Draw(shader, "moon");


            sunShader.activate();
            sunShader.setMat4("view", view);
            sunShader.setMat4("projection", projection);
            sun.render(sunShader);

            screen.newFrame();
        }
        glfwPollEvents();
    }

    earth.cleanup();
    moon.cleanup();
    sun.cleanup();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput()
{
    if (Keyboard::key(GLFW_KEY_ESCAPE))
        screen.setShouldClose(true);

    if (Keyboard::keyWentUp(GLFW_KEY_SPACE)) { 
        sleep = !sleep;
        if (sleep == 1) {
            pauseFrame = static_cast<float>(glfwGetTime()); // keep the last frame before pause
        }
        else {
            glfwSetTime(pauseFrame);  // set the time as the last frame before pause
        }
    }

    if (!sleep) {  
        if (Keyboard::key(GLFW_KEY_UP))
            camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
        if (Keyboard::key(GLFW_KEY_DOWN))
            camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
        if (Keyboard::key(GLFW_KEY_LEFT))
            camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
        if (Keyboard::key(GLFW_KEY_RIGHT))
            camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
        if (Keyboard::key(GLFW_KEY_W))
            camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
        if (Keyboard::key(GLFW_KEY_S))
            camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    }
}

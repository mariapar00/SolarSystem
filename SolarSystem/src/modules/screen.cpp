#include "screen.h"

unsigned int Screen::SCR_WIDTH = 1000;
unsigned int Screen::SCR_HEIGHT = 600;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Screen::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

Screen::Screen() : window(nullptr) {}

bool Screen::init() {
    // glfw window creation
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Planets", NULL, NULL);
    if (!window)
    {
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

void Screen::setParameters() {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, Screen::framebufferSizeCallback);

    glfwSetKeyCallback(window, Keyboard::keyCallback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
}

void Screen::update() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
void Screen::newFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents(); // processes only those events that have already been received and then returns immediately
}

bool Screen::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Screen::setShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(window, shouldClose);
}


//
// Created by rooster on 09/10/24.
//
#include <glad/glad.h>

#include "MyWindow.h"
#include "Input.h"


#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

WindowData MyWindow::windowData = WindowData();

MyWindow::MyWindow(int width, int height, const char *title) {
    windowData.title = title;
    windowData.size = std::make_pair(width, height);
    initialize();
    glfwSetInputMode(windowData.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

WindowData &MyWindow::getWindowData() {
    return windowData;
}

void MyWindow::initialize() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    windowData.window = glfwCreateWindow(windowData.size.first, windowData.size.second, windowData.title, nullptr,
                                         nullptr);
    if (!windowData.window) {
        throw std::runtime_error("Failed to create GLFW window");
        terminate();
    }
    glfwMakeContextCurrent(windowData.window);
    glfwSetWindowUserPointer(windowData.window, &windowData);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        terminate();
    }
    glClearColor(0.1f, 0.7f, 0.8f, 1.0f);
    glViewport(0, 0, windowData.size.first, windowData.size.second);
    glfwGetFramebufferSize(windowData.window, &windowData.size.first, &windowData.size.second);
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(windowData.window, framebuffer_size_callback);
    glfwSetKeyCallback(windowData.window, key_callback);
}

void MyWindow::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MyWindow::terminate() {
    glfwTerminate();
}

void MyWindow::pollEvents() {
    glfwPollEvents();
}

void MyWindow::swapBuffers() {
    if (windowData.window) {
        glfwSwapBuffers(windowData.window);
    }
}

bool MyWindow::isClosed() {
    return glfwWindowShouldClose(windowData.window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    MyWindow::getWindowData().size.first = width;
    MyWindow::getWindowData().size.second = height;
    printf("Framebuffer size: %dx%d\n", width, height);
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
}

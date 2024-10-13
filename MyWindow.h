//
// Created by rooster on 09/10/24.
//

#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <utility>
#include <GLFW/glfw3.h>


class GLFWwindow;

struct WindowData {
    GLFWwindow *window{nullptr};
    const char *title{};
    std::pair<int, int> size{}; //x, y

    [[nodiscard]] float aspectRatio() const {
        return static_cast<float>(size.first) / static_cast<float>(size.second);
    }

    [[nodiscard]] std::pair<int, int> cursorPosition() const {
        std::pair<double, double> mousePosition;
        glfwGetCursorPos(window, &mousePosition.first, &mousePosition.second);
        return mousePosition;
    }
};

class MyWindow {
private:
    static WindowData windowData;

public:
    MyWindow(int width, int height, const char *title);;

    static WindowData &getWindowData();

    static void initialize();

    static void clearBuffer();

    static void terminate();

    static void pollEvents();

    static void swapBuffers();

    static bool isClosed();
};


#endif //MYWINDOW_H

//
// Created by rooster on 10/10/24.
//

#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>

#include "MyWindow.h"

class KeyInput {
    // Main KeyInput functionality
private:
    // Used internally to update key states.  Called by the GLFW callback.
    void setIsKeyDown(int key, bool isDown);

    // Map from monitored keys to their pressed states
    std::unordered_map<int, bool> _keys;

    // If disabled, KeyInput.getIsKeyDown always returns false
    bool _isEnabled;

    // The GLFW callback for key events.  Sends events to all KeyInput instances
    static void callback(
        GLFWwindow *window, int key, int scancode, int action, int mods);

    // Keep a list of all KeyInput instances and notify them of all key events
    static std::vector<KeyInput *> _instances;

public:
    // Takes a list of which keys to keep state for
    explicit KeyInput(const std::vector<int> &keysToMonitor);

    ~KeyInput();

    // If this KeyInput is enabled and the given key is monitored,
    // returns pressed state.  Else returns false.
    bool getIsKeyDown(int key);

    // See _isEnabled for details
    bool getIsEnabled() const;

    void setIsEnabled(bool value);

    [[nodiscard]] std::unordered_map<int, bool> getKeys() const {
        return _keys;
    }

    // Workaround for C++ class using a c-style-callback
    // Must be called before any KeyInput instances will work
    static void setupKeyInputs();
};


class MouseInput {
private:
    float yaw = -90.0f; // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0f / 2.0;
    bool firstMouse = true;
    const float sensitivity = 0.1f;

public:
    void update() {
        double xpos{}, ypos{};
        const auto &window = MyWindow::getWindowData().window;
        glfwGetCursorPos(window, &xpos, &ypos);

        //runs once on first run, ignore
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        //find change in mouse position since last update
        float xoffset = static_cast<float>(xpos) - lastX;
        float yoffset = lastY - static_cast<float>(ypos); // Reversed since y-coordinates go from bottom to top
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    [[nodiscard]] float getYaw() const {
        return yaw;
    }

    [[nodiscard]] float getPitch() const {
        return pitch;
    }
};

#endif //INPUT_H

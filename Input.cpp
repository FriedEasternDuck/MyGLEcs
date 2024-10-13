//
// Created by rooster on 10/10/24.
//

#include "Input.h"
#include <algorithm>
#include "MyWindow.h"

std::vector<KeyInput *> KeyInput::_instances;

KeyInput::KeyInput(const std::vector<int>& keysToMonitor) : _isEnabled(true) {
    for (int key: keysToMonitor) {
        _keys[key] = false;
    }
    // Add this instance to the list of instances
    KeyInput::_instances.push_back(this);
}

KeyInput::~KeyInput() {
    // Remove this instance from the list of instances
    std::erase(_instances, this);
}

bool KeyInput::getIsKeyDown(int key) {
    bool result = false;
    if (_isEnabled) {
        if (const auto it = _keys.find(key); it != _keys.end()) {
            result = _keys[key];
        }
    }
    return result;
}

bool KeyInput::getIsEnabled() const { return _isEnabled; }

void KeyInput::setIsKeyDown(int key, bool isDown) {
    if (const auto it = _keys.find(key); it != _keys.end()) {
        _keys[key] = isDown;
    }
}

void KeyInput::setIsEnabled(const bool value) { _isEnabled = value; }

void KeyInput::setupKeyInputs() {
    //MUST BE CALLED FOR INPUT TO WORK
    glfwSetKeyCallback(MyWindow::getWindowData().window, KeyInput::callback);
}

void KeyInput::callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Send key event to all KeyInput instances
    for (KeyInput *keyInput: _instances) {
        keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}

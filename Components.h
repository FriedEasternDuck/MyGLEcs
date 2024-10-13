//
// Created by rooster on 09/10/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glad/glad.h>
#include <memory>
#include <print>
#include <glm/glm.hpp>

#include "Camera.hpp"


typedef unsigned int uint;

struct PositionComponent {
    glm::vec3 position{};

    // Equality operator
    bool operator==(const PositionComponent &other) const {
        return position == other.position;
    }

    // Inequality operator
    bool operator!=(const PositionComponent &other) const {
        return !(*this == other);
    }

    // Assignment operator
    PositionComponent &operator=(const PositionComponent &other) {
        if (this != &other) {
            position = other.position;
        }
        return *this;
    }
};

struct MovementComponent {
    glm::vec3 velocity{};
    glm::vec3 acceleration{};
    float movementSpeed{};

    explicit MovementComponent(float movementSpeed) : movementSpeed(movementSpeed) {
    }

    // Equality operator
    bool operator==(const MovementComponent &other) const {
        return velocity == other.velocity &&
               acceleration == other.acceleration &&
               movementSpeed == other.movementSpeed;
    }

    // Inequality operator
    bool operator!=(const MovementComponent &other) const {
        return !(*this == other);
    }

    // Assignment operator
    MovementComponent &operator=(const MovementComponent &other) {
        if (this != &other) {
            velocity = other.velocity;
            acceleration = other.acceleration;
            movementSpeed = other.movementSpeed;
        }
        return *this;
    }
};

struct BufferContainer {
    BufferContainer() = default;

    ~BufferContainer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    uint VAO{0}, VBO{0}, EBO{0};

    friend bool operator==(const BufferContainer &lhs, const BufferContainer &rhs) {
        return lhs.VAO == rhs.VAO
               && lhs.VBO == rhs.VBO
               && lhs.EBO == rhs.EBO;
    }

    friend bool operator!=(const BufferContainer &lhs, const BufferContainer &rhs) {
        return !(lhs == rhs);
    }

    BufferContainer &operator=(const BufferContainer *buffer_component) {
        VAO = buffer_component->VAO;
        VBO = buffer_component->VBO;
        EBO = buffer_component->EBO;
        return *this;
    };
};

struct BufferComponent {
    explicit BufferComponent(const std::shared_ptr<BufferContainer> &bufferContainer) : buffer(bufferContainer) {
    }

    std::shared_ptr<BufferContainer> buffer;

    friend bool operator==(const BufferComponent &lhs, const BufferComponent &rhs) {
        return lhs.buffer == rhs.buffer;
    }

    friend bool operator!=(const BufferComponent &lhs, const BufferComponent &rhs) {
        return !(lhs == rhs);
    }
};

struct CameraComponent {
    std::shared_ptr<Camera> camera;

    explicit CameraComponent(Camera camera): camera(std::make_shared<Camera>(camera)) {
    }

    friend bool operator==(const CameraComponent &lhs, const CameraComponent &rhs) {
        return lhs.camera->getTargetEntity() == rhs.camera->getTargetEntity();
    }
};

#endif //COMPONENTS_H

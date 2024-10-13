//
// Created by rooster on 13/10/24.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include "fwd.h"
#include "Input.h"


class Camera {
private:
    Entity targetEntity;
    glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};

public:
    explicit Camera(const Entity target) : targetEntity(target) {};

    static constexpr glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};

    [[nodiscard]] glm::vec3 getCameraFront() const {
        return cameraFront;
    }

    [[nodiscard]] Entity getTargetEntity() const {
        return targetEntity;
    }
    void update(const MouseInput &mouseInput) {
        // Calculate new front vector
        std::println("Called camera update");
        glm::vec3 front{};
        front.x = cos(glm::radians(mouseInput.getYaw())) * cos(glm::radians(mouseInput.getPitch()));
        front.y = sin(glm::radians(mouseInput.getPitch()));
        front.z = sin(glm::radians(mouseInput.getYaw())) * cos(glm::radians(mouseInput.getPitch()));
        cameraFront = glm::normalize(front);
    }


};


#endif //CAMERA_HPP

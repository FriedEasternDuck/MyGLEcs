//
// Created by rooster on 10/10/24.
//

#include "MovementSystem.h"
#include "World.h"

MovementSystem::MovementSystem(): keyInput({GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D}) {
    KeyInput::setupKeyInputs();
    keyInput.setIsEnabled(true);
}

void MovementSystem::setControlledEntity(const Entity entity, const std::shared_ptr<World> &world) {
    assert(
        entity != 0 && "Attempting to assign Entity 0 to controlledEntity MovementSystem::setControlledEntity()");
    activeEntity.controlledEntity = entity;
    activeEntity.controlledPosition = &world->entityManager->getComponentFromEntity<PositionComponent>(entity);
    activeEntity.controlledMovement = &world->entityManager->getComponentFromEntity<MovementComponent>(entity);
}

void MovementSystem::update(World &world, double dt) {
    assert(activeEntity.controlledEntity !=0 && "Attempting to control Entity 0");
    if (keyInput.getIsEnabled()) {

        mouseInput.update();
        // Get controlled entity components
        const auto &movement = activeEntity.controlledMovement;
        const auto &camera = world.entityManager->getComponentFromEntity<CameraComponent>(activeEntity.controlledEntity).camera;
        auto &position = activeEntity.controlledPosition->position;
        std::println("Called movement update");
        camera->update(mouseInput);

        glm::vec3 movementDirection{};
        // Calculate movement direction
        if (keyInput.getIsEnabled()) {
            const auto& keys = keyInput.getKeys();
            if (keys.at(GLFW_KEY_W)) movementDirection += camera->getCameraFront();
            if (keys.at(GLFW_KEY_S)) movementDirection -= camera->getCameraFront();
            if (keys.at(GLFW_KEY_A)) movementDirection -= glm::normalize(glm::cross(camera->getCameraFront(), Camera::cameraUp));
            if (keys.at(GLFW_KEY_D)) movementDirection += glm::normalize(glm::cross(camera->getCameraFront(), Camera::cameraUp));
        }
        // Normalize movement direction
        if (glm::length(movementDirection) > 0.0f) {
            movementDirection = glm::normalize(movementDirection);
        }

        // Apply movement
        position += movementDirection * movement->movementSpeed * static_cast<float>(dt);

    }
}


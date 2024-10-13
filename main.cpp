//
// Created by rooster on 08/10/24.
//
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Buffers.h"

#include "Components.h"
#include "EntityManager.h"
#include "MovementSystem.h"
#include "MyWindow.h"
#include "Primitives.h"
#include "Shader.h"
#include "Texture.h"
#include "World.h"
#include "ReferanceCubes.hpp"


int main() {
    //KEY OBJECTS
    MyWindow gameWindow(800, 600, "Title");
    KeyInput utilInput(std::vector<int>{GLFW_KEY_ESCAPE});
    Buffers buffers;
    const auto world = std::make_shared<World>();
    const auto &entityManager = world->entityManager;
    const auto movementSystem = std::make_shared<MovementSystem>();

    //WORLD SETUP
    world->registerComponent<PositionComponent>();
    world->registerComponent<BufferComponent>();
    world->registerComponent<MovementComponent>();
    world->registerComponent<CameraComponent>();
    world->registerSystem(movementSystem);



    //entity creation
    const auto player = entityManager->createEntity();
    entityManager->addComponentToEntity(player, PositionComponent({0, 0, 0}));
    entityManager->addComponentToEntity(player, BufferComponent({buffers.cubeBuffer}));
    entityManager->addComponentToEntity(player, MovementComponent(6.0f));
    entityManager->addComponentToEntity(player, CameraComponent(Camera(player)));

    //REFERENCE CUBES
    std::vector<Entity> refCubeEntityVector{};
    for (ReferenceCubes refCubes; auto &cubePos: refCubes.cubes) {
        auto id = entityManager->createEntity();
        entityManager->addComponentToEntity(id, BufferComponent({buffers.cubeBuffer}));
        entityManager->addComponentToEntity(id, PositionComponent({cubePos}));
        refCubeEntityVector.push_back(id);
    }

    //rendering setup
    Shader shader("../Shaders/cubeVertex.glsl", "../Shaders/cubeFragment.glsl");
    shader.use();
    const Texture texture("../textures/tile019.png");
    texture.bind();

    //MOVEMENT SETUP

    movementSystem->setControlledEntity(player, world);

    //main loop
    while (!MyWindow::isClosed()) {
        MyWindow::clearBuffer();
        auto &playerPos = entityManager->getComponentFromEntity<PositionComponent>(player).position;


        //MATRICES
        auto model = glm::mat4();
        auto projection = glm::mat4();
        auto view = glm::mat4();

        //PROJECTION
        projection = glm::perspective(glm::radians(45.0f), MyWindow::getWindowData().aspectRatio(), 0.1f, 100.0f);
        shader.setMat4("projection", projection);
        //VIEW
        auto cameraFront = entityManager->getComponentFromEntity<CameraComponent>(player).camera->getCameraFront();
        auto cameraPosRelative = playerPos - cameraFront * 5.0f + glm::vec3(0.0f, 1.0f, 0.0f);
        view = glm::lookAt(cameraPosRelative, playerPos, glm::vec3(0, 1, 0));
        shader.setMat4("view", view);
        //MODEL
        model = glm::mat4(1.0f);
        model = glm::translate(model, entityManager->getComponentFromEntity<PositionComponent>(player).position);
        shader.setMat4("model", model);

        //DRAWING
        //draw "player" cube
        glBindVertexArray(world->entityManager->getComponentFromEntity<BufferComponent>(player).buffer->VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Primitives::cubeIndices.size()), GL_UNSIGNED_INT, nullptr);
        //draw ref cubes
        for (auto &cubeEntity: refCubeEntityVector) {
            model = glm::mat4(1.0f);
            model = glm::translate(
                model, entityManager->getComponentFromEntity<PositionComponent>(cubeEntity).position);
            shader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Primitives::cubeIndices.size()), GL_UNSIGNED_INT,
                           nullptr);
        }

        world->update();

        if (utilInput.getIsKeyDown(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(MyWindow::getWindowData().window, true);
        }

        MyWindow::pollEvents();
        MyWindow::swapBuffers();
    }


    return 0;
}

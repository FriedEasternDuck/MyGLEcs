//
// Created by rooster on 09/10/24.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ComponentManager.h"
#include "fwd.h"
#include "MovementSystem.h"


class EntityFactory;
class EntityManager;


class World {
private:
    std::shared_ptr<ComponentManager> componentManager;
    std::shared_ptr<EntityFactory> entityFactory;
    std::vector<std::shared_ptr<System> > systems;
    double deltaTime;
    double lastTime;

public:
    World();

    std::unique_ptr<EntityManager> entityManager;

    template<typename T>
    void registerComponent() const {
        componentManager->registerComponent<T>();
    }

    void registerSystem(const std::shared_ptr<System>& system) {
        systems.push_back(system);
    }

    void update() {
        calculateDeltaTime();
        for (const auto &system: systems) {
            system->update(*this, deltaTime);
        }
    };

    template<typename T>
    [[nodiscard]] std::shared_ptr<IComponentArray> &getComponentArray() const {
        return componentManager->getComponentArray<T>();
    }

    void calculateDeltaTime() {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    };


    [[nodiscard]] double getDeltaTime() const {
        return deltaTime;
    }

};


#endif //WORLD_H

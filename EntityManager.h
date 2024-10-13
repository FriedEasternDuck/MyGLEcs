//
// Created by rooster on 10/10/24.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>
#include <utility>

#include "fwd.h"
#include "ComponentManager.h"
#include "EntityFactory.h"


enum class EntityType {
    Player,
    Enemy
};


class EntityManager {
private:
    std::shared_ptr<ComponentManager> componentManager;
    std::shared_ptr<EntityFactory> entityFactory;

public:
    EntityManager(const std::shared_ptr<ComponentManager> &componentManager, const std::shared_ptr<EntityFactory> &entityFactory) {
        this->componentManager = componentManager;
        this->entityFactory = entityFactory;
    };

    [[nodiscard]] Entity createEntity() const {
        return entityFactory->createNewEntity();
    };

    void destroyEntity(const Entity entity) const {
        entityFactory->destroyEntity(entity);
        componentManager->entityDestroyed(entity);
    };

    template<typename T>
    Entity getEntityFromComponent();

    template<typename T>
    T& getComponentFromEntity(Entity entity);

    template<typename T>
    void addComponentToEntity(Entity entity, T component);

    template<typename T>
    void removeComponentFromEntity(Entity entity) const;
};

template<typename T>
Entity EntityManager::getEntityFromComponent() {
    return componentManager->getEntityFromComponent<T>();
}

template<typename T>
T& EntityManager::getComponentFromEntity(Entity entity) {
    return componentManager->getComponentFromEntity<T>(entity);
}

template<typename T>
void EntityManager::addComponentToEntity(Entity entity, T component) {

    componentManager->addComponent(entity, component);
}

template<typename T>
void EntityManager::removeComponentFromEntity(Entity entity) const {
    componentManager->removeComponent<T>(entity);
}


#endif //ENTITYFACTORY_H

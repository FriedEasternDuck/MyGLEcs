//
// Created by rooster on 09/10/24.
//

#include "World.h"
#include "ComponentManager.h"
#include "EntityManager.h"

World::World() : componentManager(std::make_shared<ComponentManager>()),
                 entityFactory(std::make_shared<EntityFactory>()),
                 entityManager(std::make_unique<EntityManager>(componentManager, entityFactory)) {
}

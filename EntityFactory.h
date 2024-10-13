#pragma once
#include <vector>
#include "fwd.h"

#define ENTITY_GENERATION_BITS 8
#define ENTITY_ID_BITS 24
#define MAX_ENTITIES 0xFFFFFF

#define ENTITY_ID_MASK 0x00FFFFFF
#define ENTITY_GENERATION_MASK 0xFF000000
#define ENTITY_GET_GENERATION(entity) (entity & ENTITY_GENERATION_MASK) >> ENTITY_ID_BITS
#define ENTITY_GET_ID(entity) (entity & ENTITY_ID_MASK)

class EntityFactory {
private:
    std::vector<Entity> freeEntities;
    static Entity NEXT_ENTITY_ID;

    // Helper function to increment generation
    static Entity incrementGeneration(Entity entity);

public:
    Entity createNewEntity();

    void destroyEntity(Entity entity);

    bool isEntityValid(Entity entity);
};
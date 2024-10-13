#include "EntityFactory.h"

#include <print>


Entity EntityFactory::incrementGeneration(Entity entity) {
    uint32_t generation = (entity & ENTITY_GENERATION_MASK) >> ENTITY_ID_BITS;
    uint32_t id = entity & ENTITY_ID_MASK;
    generation = (generation + 1) & 0xFF; // Wrap around after 255
    return (generation << ENTITY_ID_BITS) | id;
}

Entity EntityFactory::createNewEntity() {
    if (!freeEntities.empty()) {
        Entity recycledEntity = freeEntities.back();
        freeEntities.pop_back();
        auto newEntity = incrementGeneration(recycledEntity);
        std::println("Entity recycled: {0}, {1}", ENTITY_GET_ID(newEntity), ENTITY_GET_GENERATION(newEntity));
        return newEntity;
    }
    if (NEXT_ENTITY_ID <= MAX_ENTITIES) {
        return NEXT_ENTITY_ID++; // Generation starts at 0 for new entities
    }
    throw std::runtime_error("Maximum number of entities reached");
}

void EntityFactory::destroyEntity(Entity entity) {
    uint32_t id = entity & ENTITY_ID_MASK;
    freeEntities.push_back(entity); // Store the full entity, including generation
}

bool EntityFactory::isEntityValid(Entity entity) {
    return std::ranges::find(freeEntities, entity) == freeEntities.end();
}

Entity EntityFactory::NEXT_ENTITY_ID = 1;

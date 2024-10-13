//
// Created by rooster on 09/10/24.
//

#include "ComponentManager.h"
#include "ComponentArray.h"



void ComponentManager::entityDestroyed(Entity entity) const {
    for (auto const &pair: mComponentArrays) {
        auto const &component = pair.second;
        component->entityDestroyed(entity);
    }
}

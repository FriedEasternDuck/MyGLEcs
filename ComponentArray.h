//
// Created by rooster on 09/10/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include "EntityFactory.h"


class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
private:
    std::vector<T> mComponentArray{};
    std::unordered_map<Entity, size_t> mEntityToIndexMap{};
    std::unordered_map<size_t, Entity> mIndexToEntityMap{};
    size_t mSize{};

public:
    void insertData(const Entity entity, T component) {
        assert(
            !mEntityToIndexMap.contains(entity)&&
            "Component added to same entity more than once.");
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray.insert(mComponentArray.begin() + newIndex, component);
        ++mSize;
    }

    Entity getEntity(T &component) {
        auto it = std::find(mComponentArray.begin(), mComponentArray.end(), component);
        assert(it != mComponentArray.end() && "Component does not belong to any entity.");
        size_t index = std::distance(mComponentArray.begin(), it);
        return mIndexToEntityMap[index];
    }

    T &getData(Entity entity) {
        assert(mEntityToIndexMap.contains(entity)&& "Retrieving non-existent component.");
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void removeData(Entity entity) {
        assert(mEntityToIndexMap.contains(entity)&& "Removing non-existent component.");

        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfLastElement);

        --mSize;
    }

    void entityDestroyed(Entity entity) override {
        if (mEntityToIndexMap.contains(entity)) {
            removeData(entity);
        }
    }




};


#endif //COMPONENT_H

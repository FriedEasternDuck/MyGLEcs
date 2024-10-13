//
// Created by rooster on 09/10/24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "ComponentArray.h"
#include "EntityFactory.h"

class IComponentArray;
template<class T>
class ComponentArray;


class ComponentManager {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray> > mComponentArrays{};
    std::unordered_map<std::type_index, std::size_t> mComponentTypes{};
    std::size_t mNextComponentType{};

public:
    template<typename T>
    void registerComponent();;

    template<typename T>
    void addComponent(Entity entity, T component);;

    template<typename T>
    void removeComponent(Entity entity);;

    template<typename T>
    std::shared_ptr<ComponentArray<T> > getComponentArray();;

    template<typename T>
    T &getComponentFromEntity(Entity entity);;

    template<typename T>
    Entity getEntityFromComponent(T &component);

    void entityDestroyed(Entity entity) const;
};

template<typename T>
std::shared_ptr<ComponentArray<T> > ComponentManager::getComponentArray() {
    const auto type = std::type_index(typeid(T));
    assert(mComponentArrays.contains(type)&& "Component not registered before use.");
    return std::static_pointer_cast<ComponentArray<T> >(mComponentArrays[type]);
}

template<typename T>
void ComponentManager::registerComponent() {
    auto type = std::type_index(typeid(T));
    // Use find instead of contains to ensure compatibility with different C++ standards
    assert(!mComponentArrays.contains(type)&& "Registering component type more than once.");
    mComponentArrays.insert({type, std::make_shared<ComponentArray<T> >()});
    mComponentTypes.insert({type, mNextComponentType++});
}

template<typename T>
void ComponentManager::addComponent(Entity entity, T component) {
    auto compArray = getComponentArray<T>();
    compArray->insertData(entity, component);
}

template<typename T>
void ComponentManager::removeComponent(Entity entity) {
    getComponentArray<T>()->removeData(entity);
}

template<typename T>
T &ComponentManager::getComponentFromEntity(Entity entity) {
    return getComponentArray<T>()->getData(entity);
}

template<typename T>
Entity ComponentManager::getEntityFromComponent(T &component) {
    auto componentArray = getComponentArray<T>();
    return componentArray->getEntity(component);
}


#endif //COMPONENTMANAGER_H

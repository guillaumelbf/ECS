#pragma once

#include <unordered_map>
#include <memory>

#include "types.hpp"
#include "componentArray.hpp"

class ComponentManager
{
private:

    std::unordered_map<const char*, ComponentType> componentTypes {};

    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays {};

    ComponentType nextComponentType {};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

public:

    template<typename T>
    void RegisterComponent();

    template<typename T>
    ComponentType GetComponentType();

    template<typename T>
    void AddComponent(Entity _entity, T _component);

    template<typename T>
    void RemoveComponent(Entity _entity);

    template<typename T>
    T& GetComponent(Entity _entity);

    void EntityDestroyed(Entity _entity);
};

#include "componentManager.inl"
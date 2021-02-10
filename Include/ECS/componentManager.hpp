#pragma once

#include <iostream>
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
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        if(componentTypes.find(typeName) == componentTypes.end())
        {
            std::cerr << "Error : Cannot get component array (Component not registered)" << std::endl;
            return nullptr;
        }

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }

public:

    template<typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();

        if(componentTypes.find(typeName) != componentTypes.end())
        {
            std::cerr << "Error : Cannot register component type (Component type already registered)" << std::endl;
            return;
        }

        componentTypes.insert({typeName,nextComponentType});

        componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        nextComponentType++;
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        const char* typeName = typeid(T).name();

        if(componentTypes.find(typeName) == componentTypes.end())
        {
            std::cerr << "Error : Cannot get component type (Component not registered)" << std::endl;
            return 0;
        }

        return componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity _entity, T _component)
    {
        GetComponentArray<T>()->InsertData(_entity, _component);
    }

    template<typename T>
    void RemoveComponent(Entity _entity)
    {
        GetComponentArray<T>()->RemoveData(_entity);
    }

    template<typename T>
    T& GetComponent(Entity _entity)
    {
        return GetComponentArray<T>()->GetData(_entity);
    }

    void EntityDestroyed(Entity _entity)
    {
        for (auto const& pair : componentArrays)
        {
            auto const& component = pair.second;

            component->EntityDestroyed(_entity);
        }
    }
};
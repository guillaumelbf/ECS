#include "componentManager.hpp"

#include <iostream>

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
    const char* typeName = typeid(T).name();

    if(componentTypes.find(typeName) == componentTypes.end())
    {
        std::cerr << "Error : Cannot get component array (Component not registered)" << std::endl;
        return nullptr;
    }

    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
}

template<typename T>
void ComponentManager::RegisterComponent()
{
    const char* typeName = typeid(T).name();

    if(componentTypes.find(typeName) != componentTypes.end())
    {
        std::cerr << "Error : Cannot register component type (Component type already registered)" << std::endl;
        return;
    }

    componentTypes.insert({typeName,nextComponentType});

    componentTypes.insert({typeName, std::make_shared<ComponentArray<T>>()});

    nextComponentType++;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
    const char* typeName = typeid(T).name();

    if(componentTypes.find(typeName) != componentTypes.end())
    {
        std::cerr << "Error : Cannot get component type (Component not registered)" << std::endl;
        return 0;
    }

    return componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity _entity, T _component)
{
    GetComponentArray<T>()->InsertData(_entity, _component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity _entity)
{
    GetComponentArray<T>()->RemoveData(_entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity _entity)
{
    return GetComponentArray<T>()->GetData(_entity);
}

void ComponentManager::EntityDestroyed(Entity _entity)
{
    for (auto const& pair : componentArrays)
    {
        auto const& component = pair.second;

        component->EntityDestroyed(_entity);
    }
}
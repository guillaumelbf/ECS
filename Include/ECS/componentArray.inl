#include "ECS/componentArray.hpp"

#include <iostream>

template<typename T>
void ComponentArray<T>::InsertData(Entity _entity, T _component)
{
    if(entityToIndexMap.find(_entity) != entityToIndexMap.end())
    {
        std::cerr << "Error : Cannot add component (Component already exist)" << std::endl;
        return;
    }

    size_t newIndex             = size;
    entityToIndexMap[_entity]   = newIndex;
    indexToEntityMap[newIndex]  = _entity;
    componentArray[newIndex]    = _component;

    size++;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity _entity)
{
    if(entityToIndexMap.find(_entity) == entityToIndexMap.end())
    {
        std::cerr << "Error : Cannot remove component (Component doesn't exist)" << std::endl;
        return;
    }

    size_t indexOfRemovedEntity             = entityToIndexMap[_entity];
    size_t indexOfLastElement               = size-1;
    componentArray[indexOfRemovedEntity]    = componentArray[indexOfLastElement];

    Entity entityOfLastElement              = indexToEntityMap[indexOfLastElement];
    entityToIndexMap[entityOfLastElement]   = indexOfRemovedEntity;
    indexToEntityMap[indexOfRemovedEntity]  = entityOfLastElement;

    entityToIndexMap.erase(_entity);
    indexToEntityMap.erase(indexOfLastElement);

    size--;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity _entity)
{
    if(entityToIndexMap.find(_entity) == entityToIndexMap.end())
    {
        std::cerr << "Error : Cannot get component (Component doesn't exist)" << std::endl;
        return;
    }

    return componentArray[entityToIndexMap[_entity]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity _entity)
{
    if(entityToIndexMap.find(_entity) != entityToIndexMap.end())
    {
        RemoveData(_entity);
    }
}
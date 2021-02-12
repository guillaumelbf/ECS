#pragma once

#include <array>
#include <unordered_map>

#include "ECS/types.hpp"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;

    virtual void EntityDestroyed(Entity _entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:

    std::array<T, MAX_ENTITIES> componentArray {};

    std::unordered_map<Entity, size_t> entityToIndexMap {};
    std::unordered_map<size_t, Entity> indexToEntityMap {};

    size_t size {};

public:

    void InsertData(Entity _entity, T _component)
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

    void RemoveData(Entity _entity)
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

    T& GetData(Entity _entity)
    {
        try
        {
            return componentArray.at(entityToIndexMap.at(_entity));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error : Cannot get component (Component doesn't exist)" << std::endl;
            abort();
        }
    }

    void EntityDestroyed(Entity _entity) final
    {
        if(entityToIndexMap.find(_entity) != entityToIndexMap.end())
        {
            RemoveData(_entity);
        }
    }
};


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

    void InsertData(Entity _entity, T _component);

    void RemoveData(Entity _entity);

    T& GetData(Entity _entity);

    void EntityDestroyed(Entity _entity) final;
};

#include "componentArray.inl"


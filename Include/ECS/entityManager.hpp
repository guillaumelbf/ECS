#pragma once

#include <queue>
#include <array>

#include "ECS/types.hpp"

class EntityManager
{
private:
    std::queue<Entity> availableEntities {};
    std::array<Signature, MAX_ENTITIES> signatures {};

    uint32_t livingEntityCount {};
public:
    EntityManager();

    Entity CreateEntity();

    void DestroyEntity(Entity _entity);

    void SetSignature(Entity _entity, Signature _signature);

    Signature GetSignature(Entity _entity);
};

#include "entityManager.inl"


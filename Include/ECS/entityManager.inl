#include "ECS/entityManager.hpp"

#include <iostream>

EntityManager::EntityManager()
{
    for (Entity entity = 0 ; entity < MAX_ENTITIES ; entity++)
        availableEntities.push(entity);
}

Entity EntityManager::CreateEntity()
{
    //max entity guard
    if(livingEntityCount > MAX_ENTITIES)
    {
        std::cerr << "Error : Cannot create more entity (Max entities reach) : " << MAX_ENTITIES << std::endl;
        return 0;
    }

    Entity id = availableEntities.front();
    availableEntities.pop();
    livingEntityCount++;

    return id;
}

void EntityManager::DestroyEntity(Entity _entity)
{
    if(_entity > MAX_ENTITIES)
    {
        std::cerr << "Error : Cannot delete entity (Entity out of range) " << std::endl;
        return;
    }

    signatures[_entity].reset();

    availableEntities.push(_entity);
    livingEntityCount--;
}

void EntityManager::SetSignature(Entity _entity, Signature _signature)
{
    if(_entity > MAX_ENTITIES)
    {
        std::cerr << "Error : Cannot set signature (Entity out of range) " << std::endl;
        return;
    }

    signatures[_entity] = _signature;
}

Signature EntityManager::GetSignature(Entity _entity)
{
    if(_entity > MAX_ENTITIES)
    {
        std::cerr << "Error : Cannot get signature (Entity out of range) " << std::endl;
        return 0;
    }

    return signatures[_entity];
}

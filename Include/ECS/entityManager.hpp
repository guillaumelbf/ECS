#pragma once

#include <iostream>
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
    EntityManager()
    {
        for (Entity entity = 0 ; entity < MAX_ENTITIES ; entity++)
            availableEntities.push(entity);
    }

    Entity CreateEntity()
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

    void DestroyEntity(Entity _entity)
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

    void SetSignature(Entity _entity, Signature _signature)
    {
        if(_entity > MAX_ENTITIES)
        {
            std::cerr << "Error : Cannot set signature (Entity out of range) " << std::endl;
            return;
        }

        signatures[_entity] = _signature;
    }

    Signature GetSignature(Entity _entity)
    {
        if(_entity > MAX_ENTITIES)
        {
            std::cerr << "Error : Cannot get signature (Entity out of range) " << std::endl;
            return 0;
        }

        return signatures[_entity];
    }
};


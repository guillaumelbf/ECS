#include "systemManager.hpp"

#include <iostream>

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
    const char* typeName = typeid(T).name();

    if(systems.find(typeName) != systems.end())
    {
        std::cerr << "Error : Cannot register system (System already registered)" << std::endl;
        return nullptr;
    }

    auto system = std::make_shared<T>();
    systems.insert({typeName,system});

    return system;
}

template<typename T>
void SystemManager::SetSignature(Signature _signature)
{
    const char* typeName = typeid(T).name();

    if(systems.find(typeName) == systems.end())
    {
        std::cerr << "Error : Cannot set signature (System already used)" << std::endl;
        return;
    }

    signatures.insert({typeName,_signature});
}

void SystemManager::EntityDestroyed(Entity _entity)
{
    for (auto const& pair : systems)
    {
        auto const& system = pair.second;

        system->entities.erase(_entity);
    }
}

void SystemManager::EntitySignatureChanged(Entity _entity, Signature _entitySignature)
{
    for (auto const& pair : systems)
    {
        auto const& type = pair.first;
        auto const& system = pair.second;
        auto const& systemSignature = signatures[type];

        // Entity signature matches system signature - insert into set
        if ((_entitySignature & systemSignature) == systemSignature)
        {
            system->entities.insert(_entity);
        }
            // Entity signature does not match system signature - erase from set
        else
        {
            system->entities.erase(_entity);
        }
    }
}
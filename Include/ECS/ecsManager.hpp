#pragma once

#include <memory>

#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"

class ECSManager
{
private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
public:

    void Init()
    {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();
    }

    Entity CreateEntity()
    {
        return  entityManager->CreateEntity();
    }

    void DestroyEntity(Entity _entity)
    {
        entityManager->DestroyEntity(_entity);

        componentManager->EntityDestroyed(_entity);

        systemManager->EntityDestroyed(_entity);
    }

    template<typename T>
    void RegisterComponent()
    {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity _entity, T _component)
    {
        componentManager->AddComponent<T>(_entity,_component);

        auto signature = entityManager->GetSignature(_entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entityManager->SetSignature(_entity,signature);

        systemManager->EntitySignatureChanged(_entity,signature);
    }

    template<typename T>
    void RemoveComponent(Entity _entity)
    {
        componentManager->RemoveComponent<T>(_entity);

        auto signature = entityManager->GetSignature(_entity);
        signature.set(componentManager->GetComponentType<T>(), false);
        entityManager->SetSignature(_entity,signature);

        systemManager->EntitySignatureChanged(_entity,signature);
    }

    template<typename T>
    T& GetComponent(Entity _entity)
    {
        return componentManager->GetComponent<T>(_entity);
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature _signature)
    {
        systemManager->SetSignature<T>(_signature);
    }

};
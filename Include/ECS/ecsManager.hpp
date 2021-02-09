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

    void Init();

    Entity CreateEntity();

    void DestroyEntity(Entity _entity);

    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity _entity, T _component);

    template<typename T>
    void RemoveComponent(Entity _entity);

    template<typename T>
    T& GetComponent(Entity _entity);

    template<typename T>
    ComponentType GetComponentType();

    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature _signature);

};

#include "ecsManager.inl"
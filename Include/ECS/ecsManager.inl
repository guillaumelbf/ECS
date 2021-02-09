#include "ecsManager.hpp"

void ECSManager::Init()
{
    componentManager = std::make_unique<ComponentManager>();
    entityManager = std::make_unique<EntityManager>();
    systemManager = std::make_unique<SystemManager>();
}

Entity ECSManager::CreateEntity()
{
    return  entityManager->CreateEntity();
}

void ECSManager::DestroyEntity(Entity _entity)
{
    entityManager->DestroyEntity(_entity);

    componentManager->EntityDestroyed(_entity);

    systemManager->EntityDestroyed(_entity);
}

template<typename T>
void ECSManager::RegisterComponent()
{
    componentManager->RegisterComponent<T>();
}

template<typename T>
void ECSManager::AddComponent(Entity _entity, T _component)
{
    componentManager->AddComponent<T>(_entity,_component);

    auto signature = entityManager->GetSignature(_entity);
    signature.set(componentManager->GetComponentType<T>(), true);
    entityManager->SetSignature(_entity,signature);

    systemManager->EntitySignatureChanged(_entity,signature);
}

template<typename T>
void ECSManager::RemoveComponent(Entity _entity)
{
    componentManager->RemoveComponent<T>(_entity);

    auto signature = entityManager->GetSignature(_entity);
    signature.set(componentManager->GetComponentType<T>(), false);
    entityManager->SetSignature(_entity,signature);

    systemManager->EntitySignatureChanged(_entity,signature);
}

template<typename T>
T& ECSManager::GetComponent(Entity _entity)
{
    return componentManager->GetComponent<T>(_entity);
}

template<typename T>
ComponentType ECSManager::GetComponentType()
{
    return componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> ECSManager::RegisterSystem()
{
    return systemManager->RegisterSystem<T>();
}

template<typename T>
void ECSManager::SetSystemSignature(Signature _signature)
{
    systemManager->SetSignature<T>(_signature);
}
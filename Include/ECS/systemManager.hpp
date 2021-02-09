#pragma once

#include <unordered_map>
#include <memory>

#include "system.hpp"
#include "types.hpp"

class SystemManager
{
private:

    std::unordered_map<const char*, Signature> signatures{};

    std::unordered_map<const char*, std::shared_ptr<System>> systems{};

public:

    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSignature(Signature _signature);

    void EntityDestroyed(Entity _entity);

    void EntitySignatureChanged(Entity _entity, Signature _entitySignature);

};

#include "systemManager.inl"
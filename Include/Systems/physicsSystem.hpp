#pragma once

#include "ECS/system.hpp"
#include "ECS/ecsManager.hpp"

class PhysicsSystem : public System
{
private:
public:

    void Init();

    void Update(float _deltaTime, ECSManager& _ecsManager);
};
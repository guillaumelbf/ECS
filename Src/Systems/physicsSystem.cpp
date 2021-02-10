#include "Systems/physicsSystem.hpp"

#include "Components/rigidbody.hpp"
#include "Components/transform.hpp"
#include "Components/gravity.hpp"

void PhysicsSystem::Init()
{

}

void PhysicsSystem::Update(float _deltaTime,ECSManager& _ecsManager)
{
    for (auto const& entity : entities)
    {
        auto& rigidbody = _ecsManager.GetComponent<Rigidbody>(entity);
        auto& transform = _ecsManager.GetComponent<Transform>(entity);
        auto const&  gravity   = _ecsManager.GetComponent<Gravity>(entity);

        transform.position.y -= 100 * _deltaTime;
    }
}

#pragma once
#include "GameObject.h"
using namespace LVB;
class b2Body;
class b2World;
class Bubble : public GameObject
{
public:
	Bubble(b2World* world, const glm::vec2& spawnPos);

protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	b2Body* m_RigidBody;
	float m_LifeTime;
	float m_Timer;
};
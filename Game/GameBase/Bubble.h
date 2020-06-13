#pragma once
#include "GameObject.h"
using namespace LVB;
class b2Body;
class b2World;
namespace LVB
{
	class GameScene;
}
class Bubble : public GameObject
{
public:
	Bubble(b2World* world, const glm::vec2& spawnPos, GameScene* scene);
	

	void Hit() { m_IsHit = true; }
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	b2World* m_World;
	GameScene* m_Scene;
	b2Body* m_RigidBody;
	float m_LifeTime;
	float m_Timer;
	float m_AnimTime = 0;

	bool m_IsHit = false;
	void Destroy();
};
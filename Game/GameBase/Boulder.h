#pragma once
#include "GameObject.h"
class b2Body;
class b2World;
class Character;
namespace LVB
{
	class GameScene;
}
class Boulder : public LVB::GameObject
{
public:
	Boulder(b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene,float moveSpeed);
	~Boulder();
	void Hit(Character* c);

protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:

	b2World* m_World;
	LVB::GameScene* m_Scene;
	b2Body* m_RigidBody;

	float m_LifeTime;
	float m_Timer;
	float m_AnimTime = 0;
	float m_MoveSpeed;
	bool m_IsHit;
	void Destroy();
};
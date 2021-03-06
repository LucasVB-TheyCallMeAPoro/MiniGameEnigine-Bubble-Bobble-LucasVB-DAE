#pragma once
#include "GameObject.h"
class b2Body;
class b2World;
class b2Fixture;
namespace LVB
{
	class GameScene;
}
class Enemy : public LVB::GameObject
{
public:
	enum Type 
	{
		
		ZenChan =2,
		Maita = 3
		
	};
	enum State
	{
		MoveLeft,
		MoveRight,
		Attacking,
		InBubble,
		Dead
	};
	Enemy(int id,State state,Type type,glm::vec2 spawnPos, int columnCount, int rowCount, int TotalRowCount ,LVB::GameScene* scene, b2World* world, unsigned short categoryMask, unsigned short maskBits);
	~Enemy();
	void HitWall();
	b2Fixture* GetRigidBodyFixture();
	b2Fixture* GetFootSensor();
	void IncrementFootCount();
	void DecrementFootCount();

	void HitByBubble();
	void Kill();
	void BubbleExpire();
	Enemy::State GetState() const { return m_State; }
private:
	float m_AnimTime;
	Type m_Type;
	State m_State;
	b2Body* m_RigidBody;
	b2World* m_PhysicsWorld;
	LVB::GameScene* m_Scene;

	//Movement
	float m_JumpForce;
	float m_MoveSpeed;
	int m_FootContactCount = 0;
	float m_SwapTime = 1.f;
	float m_SwapTimer = 1.f;


	//attack
	State m_PrevState;
	float m_ViewRange = 150;

	float m_AttackTime = 2.f;
	float m_AttackTimer = 0.f;
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;


private:
	void MoveLeftBehavior(float elapsedSec);
	void MoveRightBehavior(float elapsedSec);
	void AttackBehavior(float elapsedSec);
	void UpdateSprite(float elapsedSec);
	void Destroy();
	void CheckSeePlayers();
};
#pragma once
#include <GameObject.h>
#include <Notifier.h>
using namespace LVB;

class b2World;
class b2Body;
namespace LVB
{
class GameScene;
}

class Character : public LVB::GameObject
{
public:
	enum Type
	{
		Bub,
		bob,
		Maita
	};
	enum State
	{
		moveLeft,
		moveRight,
		dead
	};
	Character(Character::Type type, int columnCount, int rowCount,  int TotalRowCount,b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene, unsigned short categoryMask, unsigned short maskBits);
	b2Body* GetBody() const { return m_RigidBody; }

	void Shoot();
	void Jump();
	void MoveLeft();
	void MoveRight();
	void TakeDamage();
	void AddScore(int amount);
	void NotifyUI();
	int m_FootContactCount = 0;

	LVB::Notifier<int> m_OnChangeScore;
	LVB::Notifier<int> m_OnChangeHealth;

	void SetToSpawnPos();
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	float m_AnimTime;
	Type m_Type;
	b2Body* m_RigidBody;
	b2World* m_PhysicsWorld;
	State m_State;
	LVB::GameScene* m_Scene;
	int m_Health = 4;
	int m_Score = 0;
	int m_ColumnCount;
	void InitControls();

	glm::vec2 m_SpawnPosition;
	//Movement
	float m_JumpForce;
	float m_MoveSpeed;
	//Bubbles
	float m_BubbleCooldown = 2.f;
	float m_BubbleCooldownTimer = 0.f;
	bool m_Shot;

	void SpawnAtTop();
};




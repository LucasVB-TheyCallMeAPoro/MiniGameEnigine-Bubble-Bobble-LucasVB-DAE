#pragma once
#include <GameObject.h>
#include <Notifier.h>
using namespace LVB;

class b2World;
class b2Body;
class b2Fixture;
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
		bubble
	};

	enum Player
	{
		Player1 = 1,
		Player2
	};
	Character(Player p,Character::Type type, int columnCount, int rowCount,  int TotalRowCount,b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene, unsigned short categoryMask, unsigned short maskBits);
	~Character();
	b2Fixture* GetBody() const;
	b2Fixture* GetFootSensor() const;
	void Shoot();
	void Jump();
	void MoveLeft();
	void MoveRight();
	void TakeDamage();
	void AddScore(int amount);
	void NotifyUI();


	LVB::Notifier<int> m_OnChangeScore;
	LVB::Notifier<int> m_OnChangeHealth;

	void SetToSpawnPos();
	void IncrementFootCount();
	void DecrementFootCount();
	int GetHealth() const {return m_Health;}
	bool IsGrounded() { return !m_Jumped; }
	void HitByBubble(const glm::vec3& pos, float yspeed, float time);
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	float m_AnimTime;
	Type m_Type;
	b2Body* m_RigidBody;
	b2World* m_PhysicsWorld;
	Player m_Player;
	State m_State;
	LVB::GameScene* m_Scene;
	int m_Health = 4;
	int m_Score = 0;
	int m_ColumnCount;

	//Combat
	float m_HitTimer = 0.f;
	float m_SaveTime = 1.f;
	bool m_Hit = false;
	glm::vec2 m_SpawnPosition;
	std::string* m_SensorName;
	//Movement
	float m_JumpForce;
	float m_MoveSpeed;
	bool m_Jumped;
	float m_JumpTime;
	float m_TotalJumpTime;
	int m_FootContactCount = 0;
	//Bubbles
	float m_BubbleCooldown = 1.f;
	float m_BubbleCooldownTimer = 0.f;
	bool m_Shot;
	//vs
	float m_UpwardsSpeed;
	glm::vec2 m_BubblePos;
	bool m_HitBubble;
	float m_FloatingDuration = 0;
	float m_FloatTimer = 0;
	void SpawnAtTop();
};




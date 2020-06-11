#pragma once
#include <GameObject.h>
using namespace LVB;
class b2World;
class b2Body;
class GameScene;
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
	Character(Character::Type type, int columnCount, int rowCount,  int TotalRowCount,b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene );
	b2Body* GetBody() const { return m_RigidBody; }

	void Shoot();
	void Jump();
	void MoveLeft();
	void MoveRight();
	void TakeDamage() { m_Health -= 1; }

	int m_FootContactCount = 0;
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
	int m_ColumnCount;
	void InitControls();
};




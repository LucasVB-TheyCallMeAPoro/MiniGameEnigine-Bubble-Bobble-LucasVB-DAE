#pragma once
#include "GameObject.h"

class b2World;
class b2Body;
class Character;
namespace LVB
{
	class GameScene;
}
class PickUp : public LVB::GameObject
{
public:
	enum Type
	{
		fries,
		melon
	};
	PickUp(b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene, Type t);
	~PickUp();

	void PickedUp(Character* c);
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	int m_Value;
	LVB::GameScene* m_Scene;
	b2World* m_PhysicsWorld;
	b2Body* m_Body;

	bool m_Destroy = false;

	void Destroy();
};
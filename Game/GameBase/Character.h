#pragma once
#include <GameObject.h>
using namespace LVB;
class b2World;
class b2Body;
class Character : public LVB::GameObject
{
public:
	enum Type
	{
		Bub,
		bob,
		Maita
	};
	Character(Character::Type type, int columnCount, int rowCount,  int TotalRowCount,b2World* world );
	
	void Jump();
	void MoveLeft();
	void MoveRight();

	int m_FootContactCount = 0;
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	float m_AnimTime;
	Type m_Type;
	b2Body* m_RigidBody;
	void InitControls();
};




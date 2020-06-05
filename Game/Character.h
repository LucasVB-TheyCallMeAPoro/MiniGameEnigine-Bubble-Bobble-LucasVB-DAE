#pragma once
#include <GameObject.h>
using namespace LVB;
class Character : public LVB::GameObject
{
public:
	enum Type
	{
		Bub,
		bob,
		Maita
	};
	Character(Character::Type type, int columnCount, int rowCount,  int TotalRowCount);
	
protected:
	virtual void Render() const override;
	virtual void Update(float elapsedSec) override;
private:
	Type m_Type;
};




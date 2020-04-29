#include "MiniginPCH.h"
#include "Transform.h"

LVB::Transform::Transform(bool isStatic)
	:m_Position{0,0,0}
	,m_IsStatic{isStatic}
{
}

LVB::Transform::Transform(float x, float y, float z, bool isStatic)
	:m_Position{x,y,z}
	,m_IsStatic{isStatic}
{
}

void LVB::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void LVB::Transform::Initialize()
{
}

void LVB::Transform::Update(float)
{
}

void LVB::Transform::Render() const 
{
}

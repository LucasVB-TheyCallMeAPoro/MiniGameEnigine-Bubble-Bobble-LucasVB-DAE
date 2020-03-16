#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
	:m_Position{0,0,0}
{
}

dae::Transform::Transform(float x, float y, float z)
	:m_Position{x,y,z}
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::Initialize()
{
}

void dae::Transform::Update(float)
{
}

void dae::Transform::Render() const 
{
}

#include "Bubble.h"
#include "Box2D.h"

Bubble::Bubble(b2World* world, const glm::vec2& spawnPos)
	:m_LifeTime{5}
	,m_RigidBody{nullptr}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);
	m_RigidBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(8, 8);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;

	m_RigidBody->CreateFixture(&fixtureDef);
	m_RigidBody->SetFixedRotation(true);

	m_RigidBody->ApplyForceToCenter({ 500,0 }, true);

}

void Bubble::Render() const
{
}

void Bubble::Update(float elapsedSec)
{
	m_RigidBody->SetLinearVelocity({ 0,-40 });
	m_Timer += elapsedSec;

	if (m_Timer >= m_LifeTime)
	{

	}
}

#include "Pickup.h"
#include "Box2D.h"
#include "../Scenes/BubbleBobbleScene.h"
#include "Transform.h"
#include "Character.h"
PickUp::PickUp(b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene, Type t)
	:m_Scene{scene}
	,m_PhysicsWorld{world}
	,m_Value{0}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);

	m_Body = world->CreateBody(&bodyDef);
	m_Body->SetFixedRotation(true);
	b2PolygonShape box;
	box.SetAsBox(7, 8);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = LVB::BubbleBobbleScene::PICKUP;
	fixtureDef.filter.maskBits = LVB::BubbleBobbleScene::CHARACTER;
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetUserData(this);
	switch (t)
	{
	case PickUp::fries:
		SetTexture("BBSprites/MaitaPickup.png");
		m_Value = 200;
		break;
	case PickUp::melon:
		SetTexture("BBSprites/ZenChanPickup.png");
		m_Value = 100;
		break;
	}

}

PickUp::~PickUp()
{
}

void PickUp::PickedUp(Character* c)
{
	c->AddScore(m_Value);
	m_Destroy = true;
}

void PickUp::Render() const
{
}

void PickUp::Update(float elapsedSec)
{
	this->GetTransform()->SetPosition(m_Body->GetTransform().p.x, m_Body->GetTransform().p.y,0);
	if (m_Destroy)
		Destroy();
}

void PickUp::Destroy()
{
	m_PhysicsWorld->DestroyBody(m_Body);
	m_Scene->RemoveGameObject(this);
}

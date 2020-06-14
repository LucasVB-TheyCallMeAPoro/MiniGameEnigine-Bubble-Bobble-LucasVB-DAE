#include "Bubble.h"
#include "Box2D.h"
#include "Texture2D.h"
#include "Spritesheet.h"
#include "Transform.h"
#include "GameScene.h"
#include "../Scenes/BubbleBobbleScene.h"
Bubble::Bubble(b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene)
	:m_LifeTime{5}
	,m_RigidBody{nullptr}
	,m_World{world}
	,m_Scene{scene}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);
	m_RigidBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(9,9);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = LVB::BubbleBobbleScene::BUBBLE;
	fixtureDef.filter.maskBits = LVB::BubbleBobbleScene::CHARACTER | LVB::BubbleBobbleScene::ENEMY;
	m_RigidBody->CreateFixture(&fixtureDef);
	m_RigidBody->SetFixedRotation(true);

	

	SetTexture("BBSprites/sprites1.png");
	int spriteHeight = GetTexture()->GetHeight() / 16;
	SetSprite(glm::ivec2(0, 208), GetTexture()->GetWidth() / 8, spriteHeight, 8, 1);
	m_RigidBody->ApplyForceToCenter({ 500,0 }, true);
	m_RigidBody->SetUserData(this);
}

void Bubble::Destroy()
{
	m_World->DestroyBody(m_RigidBody);
	m_Scene->RemoveGameObject(this);
	
}

void Bubble::Render() const
{
}

void Bubble::Update(float elapsedSec)
{
	m_RigidBody->SetLinearVelocity({ 0,m_RiseForce });
	auto rigPos = m_RigidBody->GetTransform();
	this->GetTransform()->SetPosition(rigPos.p.x, rigPos.p.y, 0);
	m_Timer += elapsedSec;

	if (m_Timer >= m_LifeTime || m_IsHit)
	{
		Destroy();
		return;
	}

	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.f / this->GetSprite()->GetSpriteSheet()->GetColumnCount()))
	{
		m_AnimTime = 0;
		this->GetSprite()->IncrementIndex();
	}

}

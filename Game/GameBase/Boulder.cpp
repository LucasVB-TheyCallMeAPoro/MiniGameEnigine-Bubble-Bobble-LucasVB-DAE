#include "Boulder.h"
#include "Box2D.h"
#include "Spritesheet.h"
#include "Texture2D.h"
#include "Transform.h"
#include "GameScene.h"
#include "../Scenes/BubbleBobbleScene.h"
#include "Character.h"
Boulder::Boulder(b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene,float moveSpeed)
	:m_LifeTime{ 5 }
	, m_RigidBody{ nullptr }
	, m_World{ world }
	, m_Scene{ scene }
	, m_MoveSpeed{moveSpeed}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);
	m_RigidBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(9, 9);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = LVB::BubbleBobbleScene::BOULDER;
	fixtureDef.filter.maskBits = LVB::BubbleBobbleScene::CHARACTER;
	m_RigidBody->CreateFixture(&fixtureDef);
	m_RigidBody->SetFixedRotation(true);



	SetTexture("BBSprites/MaitaAttack.png");
	int spriteHeight = GetTexture()->GetHeight();
	SetSprite(glm::ivec2(0, 0), GetTexture()->GetWidth() / 4, spriteHeight, 4, 1);
	m_RigidBody->SetUserData(this);
}

Boulder::~Boulder()
{
}

void Boulder::Hit(Character* c)
{
	c->TakeDamage();
	m_IsHit = true;
}

void Boulder::Render() const
{
}

void Boulder::Update(float elapsedSec)
{
	m_RigidBody->SetLinearVelocity({ m_MoveSpeed,0 });
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

void Boulder::Destroy()
{
	m_World->DestroyBody(m_RigidBody);
	m_Scene->RemoveGameObject(this);
}

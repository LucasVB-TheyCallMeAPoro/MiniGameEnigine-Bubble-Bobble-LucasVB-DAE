#include "Character.h"
#include "ResourceManager.h"
#include <Structs.h>
#include "Texture2D.h"
#include "SDL.h"
#include "Spritesheet.h"
#include "Box2D.h"
#include "Transform.h"
#include <iostream>
Character::Character(Character::Type type, int columnCount, int rowCount, int totalRowCount, b2World* world)
	:m_Type{type}
	,m_AnimTime{0.f}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(70, 5);
	
	m_RigidBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(8,8);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	m_RigidBody->CreateFixture(&fixtureDef);

	m_RigidBody->SetSleepingAllowed(false);
	m_RigidBody->SetAwake(true);

	
	SetTexture("BBSprites/Sprites0.png");
	int spriteHeight = GetTexture()->GetHeight() / totalRowCount;
	SetSprite(glm::ivec2(0, GetTexture()->GetHeight() / totalRowCount + static_cast<unsigned int>(m_Type) * spriteHeight * 2), GetTexture()->GetWidth() / columnCount, spriteHeight, columnCount, rowCount);
}

void Character::Render() const
{
	
}

void Character::Update(float elapsedSec)
{
	
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.f / this->GetSprite()->GetSpriteSheet()->GetColumnCount()))
	{
		m_AnimTime = 0;
		this->GetSprite()->IncrementIndex();
	}

	auto rigPos = m_RigidBody->GetTransform();
	this->GetTransform()->SetPosition(rigPos.p.x, rigPos.p.y, 0);
}
